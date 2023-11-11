class TraceLoader:
    @staticmethod
    def load_trace(fileName: str):
        '''
        trace is like:
        [
            {'function': 'MPI_Send', 'arguments': {'buf:ptr': 0x7fff23812ed23}}
        ]
        '''
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