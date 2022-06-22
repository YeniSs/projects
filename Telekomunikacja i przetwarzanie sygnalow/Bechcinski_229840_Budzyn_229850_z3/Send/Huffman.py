class Node:
    def __init__(self, freq, symbol, left=None, right=None):
        self.freq = freq
        self.symbol = symbol
        self.left = left
        self.right = right
        self.huff = ''

def createNodes(node, arr1, arr2, val=''):
    newVal = val + str(node.huff)
    if node.left:
        createNodes(node.left, arr1,arr2, newVal)
    if node.right:
        createNodes(node.right, arr1,arr2, newVal)
    if not node.left and not node.right:
        arr1.append(node.symbol)
        arr2.append(newVal)

def coding(msg):
    nodes = Huffman()
    letters = []
    code = []
    createNodes(nodes[0], letters, code)
    output = ''
    for i in msg:
        for j in range(len(letters)):
            if i == letters[j]:
                output = output + code[j]
    return output

def decoding(msg):
    nodes = Huffman()
    current_node = nodes[0]
    output = ''
    for i in msg:
        if int(i) == 0:
            current_node = current_node.left
        else:
            current_node = current_node.right
        if current_node.left is None and current_node.right is None:
            output += current_node.symbol
            current_node = nodes[0]
    return output

def Huffman():
    chars = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
             'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
             'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
             'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
             'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
             'Y', 'Z', '-', '_', '/', '"', "'", ':', ';', ')',
             '(', '!', '.', '?', ',', chr(10), ' ', '1', '2', '3',
             '4', '5', '6', '7', '8', '9', '0', '=', '@', '*']

    freq = [87, 10, 29, 47, 133, 25, 37, 84, 43, 1, 5, 55, 15, 97, 107, 24, 2, 73, 53, 85, 49, 8, 14, 1, 32, 0, 0, 0, 5, 0, 0, 1, 0, 10, 1, 0, 8, 0, 3, 0, 6, 6, 0, 1, 1, 19, 0, 0, 2, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 1, 1, 10, 24, 0, 39, 0, 265, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    nodes = []
    for x in range(len(chars)):
        nodes.append(Node(freq[x], chars[x]))

    while len(nodes) > 1:
        nodes = sorted(nodes, key=lambda x: x.freq)
        left = nodes[0]
        right = nodes[1]
        left.huff = 0
        right.huff = 1
        newNode = Node(left.freq + right.freq, left.symbol + right.symbol, left, right)
        nodes.remove(left)
        nodes.remove(right)
        nodes.append(newNode)
    return nodes




