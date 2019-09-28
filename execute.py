import funcs
funcdict={'b':funcs.down, 'f':funcs.up, 'l':funcs.left, 'r':funcs.right,
'fl':funcs.upleft, 'fr':funcs.upright, 'bl':funcs.downleft, 'br':funcs.downright}
def execute(l, moves, method):
    for move in moves:
        num=move[0]
        direction=funcdict[move[1]]
        steps=move[2]
        l=direction(l, num, steps, method)
    #place_i, place_j=funcs.mainfuncs.find(l, 12)
    #l[place_i][place_j], l[0][0]=l[0][0],l[place_i][place_j]
    return l
