class ConfigManager:
    '''
    functionList: [(functionName: str, arguments: [(argumentName: str, argumentType: str)])]
    opList: [str]
    typeList: [str]
    '''
    functionListFileName = 'configs/function_list.py'

    functionList = eval(open('configs/function_list.py').read())
    opList = eval(open('configs/op_list.py').read())
    typeList = eval(open('configs/type_list.py').read())

    @staticmethod
    def find_function(functionName: str):
        for function in ConfigManager.functionList:
            if functionName == function[0]:
                return function
        return None

    @staticmethod
    def add_function(function):
        ConfigManager.functionList.append(function)
        with open(ConfigManager.functionListFileName, 'w') as ofile:
            ofile.write(function)
        return

