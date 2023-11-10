class TraceCompressor:
    __functionList = eval(open('configs/function_list.py', 'r').read())
    __typeList = eval(open('configs/type_list.py', 'r').read())
    __opList = eval(open('configs/op_list.py', 'r').read())

    @staticmethod
    def load_trace(fileName: str) -> list:
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

    @staticmethod
    def compress(sourceFileName: str, targetFileName: str) -> None:
        trace = TraceCompressor.load_trace(sourceFileName)
        for entry in trace:
            functionName = entry['function']
            argumentList = entry['arguments']
            if functionName not in TraceCompressor.__functionList[0]:
                TraceCompressor.__functionList[0].append(functionName)
                TraceCompressor.__functionList[1].append(TraceCompressor.__extract_argument_type_info())
            

    @staticmethod
    def __extract_argument_type_info():
        pass
