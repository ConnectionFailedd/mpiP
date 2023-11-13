functionDict = {
    'MPI_Send': {'id': 1, 'arguments': {'buf': 'ptr'}}
}
functionList = [key for (key, value) in sorted(functionDict.items(), key=lambda x: x[1]['id'], reverse=False)]