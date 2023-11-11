from trace_compression.compressor.config_manage import ConfigManager
from trace_loader import TraceLoader


class Compressor:
    @staticmethod
    def compress(sourceFileName, targetFileName):
        trace = TraceLoader.load_trace(sourceFileName)
        for entry in trace:
            functionName = entry['function']
            arguments = entry['arguments']
            function = ConfigManager.find_function(functionName)
            if function is None:
                argumentTypeList = []
                for argumentNameType in arguments.keys():
                    argumentName, argumentType = argumentNameType.split(':')
                    argumentTypeList.append((argumentName, argumentType))
                function = (functionName, argumentTypeList)
                ConfigManager.add_function(function)

            for argumentName, argumentType in function[1]:
                if argumentType in ['int', 'ptr']:
                    pass
                elif argumentType == 'MPI_Op':
                    pass
                elif argumentType == 'MPI_Datatype':
                    pass
                elif argumentType == 'MPI_Group':
                    pass
                elif argumentType == 'MPI_Info':
                    pass
