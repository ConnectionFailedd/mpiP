from function_dict import functionDict, functionList
import math

mpiOpList = ['MPI_MAX', 'MPI_MIN', 'MPI_SUM', 'MPI_PROD', 'MPI_LAND', 'MPI_BAND', 'MPI_LOR', 'MPI_BOR', 'MPI_LXOR', 'MPI_BXOR', 'MPI_MAXLOC', 'MPI_MINLOC', 'USER_DEFINED']
mpiTypeList = ['MPI_CHAR', 'MPI_SHORT', 'MPI_INT', 'MPI_LONG', 'MPI_UNSIGNED_CHAR', 'MPI_SHORT', 'MPI_UNSIGNED', 'MPI_UNSIGNED_LONG', 'MPI_FLOAT', 'MPI_DOUBLE', 'MPI_LONG_DOUBLE', 'MPI_BYTE', 'MPI_PACKED']

def load_trace(fileName):
    with open(fileName) as traceFile:
        content = traceFile.read()
    lines = content.splitlines()
    if len(lines) < 200000:
        return eval(content)
    else:
        lines = lines[1 : -1]
        res = []
        for i in range(len(lines) - 1):
            res.append(eval(lines[i][ : -1]))
        res.append(eval(lines[-1]))
        return res

def get_string_list(trace):
    stringStats = {}
    for entry in trace:
        functionName = entry['function']
        arguments = entry['arguments']
        for argumentName, argumentType in functionDict[functionName]['arguments'].items():
            argumentValue = arguments[argumentName]
            if argumentType in ['MPI_Info', 'MPI_Win', 'MPI_File']:
                for key, value in argumentValue.items():
                    if key not in stringStats.keys():
                        stringStats[key] = 1
                    else:
                        stringStats[key] += 1
                    if value not in stringStats.keys():
                        stringStats[value] = 1
                    else:
                        stringStats[value] += 1
    return [key for (key, value) in sorted(stringStats.items(), key=lambda x: x[1], reverse=True)]

def encode_trace(trace, stringList):
    codeList = []
    codeList.append(len(trace))
    for entry in trace:
        functionName = entry['function']
        arguments = entry['arguments']
        codeList.append(functionDict[functionName]['id'])
        for argumentName, argumentType in functionDict[functionName]['arguments'].items():
            argumentValue = arguments[argumentName]
            if argumentType == 'int' or argumentType == 'ptr':
                codeList.append(argumentValue)
            elif argumentType == 'MPI_Op':
                codeList.append(mpiOpList.index(argumentValue))
            elif argumentType == 'MPI_Datatype':
                codeList.append(mpiTypeList.index(argumentValue))
            elif argumentType == 'MPI_Group':
                codeList.append(argumentValue['group_size'])
                codeList.append(argumentValue['group_rank'])
            elif argumentType in ['MPI_Info', 'MPI_Win', 'MPI_File']:
                codeList.append(len(argumentValue))
                for key, value in argumentValue.items():
                    codeList.append(stringList.index(key))
                    codeList.append(stringList.index(value))
    return codeList

def decode_trace(stringList, codeList):
    trace = []
    entryNumber = codeList[0]
    index = 1
    for _ in range(entryNumber):
        functionID = codeList[index]
        index += 1
        functionName = functionList[functionID]
        arguments = {}
        for argumentName, argumentType in functionDict[functionName]['arguments'].items():
            if argumentType == 'int' or argumentType == 'ptr':
                arguments[argumentName] = codeList[index]
                index += 1
            elif argumentType == 'MPI_Op':
                arguments[argumentName] = mpiOpList[codeList[index]]
                index += 1
            elif argumentType == 'MPI_Datatype':
                arguments[argumentName] = mpiTypeList[codeList[index]]
                index += 1
            elif argumentType == 'MPI_Group':
                arguments[argumentName] = {}
                arguments[argumentName]['group_size'] = codeList[index]
                index += 1
                arguments[argumentName]['group_rank'] = codeList[index]
                index += 1
            elif argumentType in ['MPI_Info', 'MPI_Win', 'MPI_File']:
                arguments[argumentName] = {}
                number = codeList[index]
                index += 1
                for _ in range(number):
                    arguments[argumentName][stringList[codeList[index]]] = stringList[codeList[index + 1]]
                    index += 2
        trace.append({'function': functionName, 'arguments': arguments})
    return trace

def add_int(bitstream, bitIndex, integer):
    if integer < 2:
        code = integer << 1
        codeLength = 2
    elif integer < 16:
        code = (integer << 2) + 1
        codeLength = 6
    else:
        integerBits = len(bin(integer)) - 2
        code = (integer << 8) + (integerBits << 2) + 3
        codeLength = 8 + integerBits
    while codeLength != 0:
        buffer = (code % (1 << (8 - (bitIndex % 8)))) << (bitIndex % 8)
        bufferLength = min(codeLength, 8 - (bitIndex % 8))
        code >>= bufferLength
        codeLength -= bufferLength
        if bitIndex % 8 == 0:
            bitstream.append(buffer)
            bitIndex += bufferLength
        else:
            bitstream[-1] |= buffer
            bitIndex += bufferLength
    return bitIndex

def add_int7(bitstream, bitIndex, integer):
    code = integer
    codeLength = 7
    while codeLength != 0:
        buffer = (code % (1 << (8 - (bitIndex % 8)))) << (bitIndex % 8)
        bufferLength = min(codeLength, 8 - (bitIndex % 8))
        code >>= bufferLength
        codeLength -= bufferLength
        if bitIndex % 8 == 0:
            bitstream.append(buffer)
            bitIndex += bufferLength
        else:
            bitstream[-1] |= buffer
            bitIndex += bufferLength
    return bitIndex

def get_bit(bitstream, bitIndex):
    byteIndex = math.floor(bitIndex / 8)
    return bitIndex + 1, (bitstream[byteIndex] >> (bitIndex % 8)) % 2

def read_int(bitstream, bitIndex):
    bitIndex, bit = get_bit(bitstream, bitIndex)
    if bit == 0:
        return get_bit(bitstream, bitIndex)
    else:
        bitIndex, bit = get_bit(bitstream, bitIndex)
        if bit == 0:
            res = 0
            for i in range(4):
                bitIndex, bit = get_bit(bitstream, bitIndex)
                res += bit << i
            return bitIndex, res
        else:
            integerLength = 0
            for i in range(6):
                bitIndex, bit = get_bit(bitstream, bitIndex)
                integerLength += bit << i
            res = 0
            for i in range(integerLength):
                bitIndex, bit = get_bit(bitstream, bitIndex)
                res += bit << i
            return bitIndex, res

def read_int7(bitstream, bitIndex):
    res = 0
    for i in range(7):
        bitIndex, bit = get_bit(bitstream, bitIndex)
        res += bit << i
    return bitIndex, res

def generate_bitstream(stringList, traceCode):
    bitIndex = 0
    bitstream = bytearray()

    bitIndex = add_int(bitstream, bitIndex, len(stringList))
    for string in stringList:
        bitIndex = add_int(bitstream, bitIndex, len(string))
        for char in string:
            bitIndex = add_int7(bitstream, bitIndex, ord(char))

    for code in traceCode:
        bitIndex = add_int(bitstream, bitIndex, code)

    return bitstream

def extract_bitstream(bitstream):
    bitIndex = 0

    bitIndex, stringNumber = read_int(bitstream, bitIndex)
    stringList = []
    for _ in range(stringNumber):
        bitIndex, stringLength = read_int(bitstream, bitIndex)
        string = ''
        for __ in range(stringLength):
            bitIndex, char = read_int7(bitstream, bitIndex)
            string += chr(char)
        stringList.append(string)

    bitIndex, entryNumber = read_int(bitstream, bitIndex)
    codeList = [entryNumber]
    for _ in range(entryNumber):
        bitIndex, functionID = read_int(bitstream, bitIndex)
        functionName = functionList[functionID]
        codeList.append(functionID)
        for argumentName, argumentType in functionDict[functionName]['arguments'].items():
            if argumentType in ['int', 'ptr', 'MPI_Op', 'MPI_Datatype']:
                bitIndex, code = read_int(bitstream, bitIndex)
                codeList.append(code)
            elif argumentType == 'MPI_Group':
                bitIndex, code = read_int(bitstream, bitIndex)
                codeList.append(code)
                bitIndex, code = read_int(bitstream, bitIndex)
                codeList.append(code)
            elif argumentType in ['MPI_Info', 'MPI_Win', 'MPI_File']:
                bitIndex, dictLength = read_int(bitstream, bitIndex)
                codeList.append(dictLength)
                for _ in range(2 * dictLength):
                    bitIndex, code = read_int(bitstream, bitIndex)
                    codeList.append(code)
    return stringList, codeList

def compress(sourceFileName, targetFileName):
    trace = load_trace(sourceFileName)
    stringList = get_string_list(trace)
    traceCode = encode_trace(trace, stringList)
    bitstream = generate_bitstream(stringList, traceCode)
    with open(targetFileName, 'wb') as targetFile:
        targetFile.write(bitstream)

def decompress(sourceFileName, targetFileName):
    with open(sourceFileName, 'rb') as sourceFile:
        bitstream = sourceFile.read()

    stringList, traceCode = extract_bitstream(bitstream)
    trace = decode_trace(stringList, traceCode)
    with open(targetFileName, 'w') as targetFile:
        targetFile.write('[\n')
        i = 0
        for entry in trace:
            targetFile.write('    {')
            functionName = entry['function']
            arguments = entry['arguments']
            targetFile.write(f'\'function\': \'{functionName}\', \'arguments\': {{')
            j = 0
            for argumentName, argumentType in functionDict[functionName]['arguments'].items():
                argumentValue = arguments[argumentName]
                if argumentType == 'int':
                    targetFile.write(f'\'{argumentName}\': {argumentValue}')
                if argumentType == 'ptr':
                    targetFile.write(f'\'{argumentName}\': {hex(argumentValue)}')
                elif argumentType == 'MPI_Op':
                    targetFile.write(f'\'{argumentName}\': \'{argumentValue}\'')
                elif argumentType == 'MPI_Datatype':
                    targetFile.write(f'\'{argumentName}\': \'{argumentValue}\'')
                elif argumentType == 'MPI_Group':
                    targetFile.write(f'\'{argumentName}\': {{\'group_size\': {argumentValue["group_size"]}, \'group_rank\': {argumentValue["group_rank"]}}}')
                elif argumentType in ['MPI_Info', 'MPI_Win', 'MPI_File']:
                    targetFile.write(f'\'{argumentName}\': {{')
                    k = 0
                    for key, value in argumentValue.items():
                        targetFile.write(f'\'{key}\': \'{value}\'')
                        if k < len(argumentValue) - 1:
                            targetFile.write(', ')
                        k += 1
                    targetFile.write(f'}}')
                if j < len(functionDict[functionName]['arguments']) - 1:
                    targetFile.write(', ')
                j += 1
            if i < len(trace) - 1:
                targetFile.write('}},\n')
            else:
                targetFile.write('}}\n')
            i += 1
        targetFile.write(']')

if __name__ == '__main__':
    compress('../trace/trace_1', 'compressed')
    decompress('compressed', 'decompressed')