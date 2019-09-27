import mainfuncs


'''the below functions are ways to shift the seats.'''


def inst(l, index, steps):
    if steps>index:
        steps=index
    lt=l[index-steps:index+1]
    lt.insert(0, lt.pop())
    l[index-steps:index+1]=lt
    return l
def swap(l, index, steps):
    if steps>index:
        steps=index
    l[index-steps], l[index]=l[index], l[index-steps]
    return l
def push(l, index, steps):
    if steps>index:
        steps=index
    for _ in range(steps):
        l.append(l.pop(0))
    return l
    
'''the below functions are used to shift seats in a given way.'''


def left(l, num, steps, func):
    place_i, place_j=mainfuncs.find(l, num)
    l[place_i]=func(l[place_i], place_j, steps)
    return l
def right(l, num, steps, func):
    place_i, place_j=mainfuncs.find(l, num)
    l[place_i]=func(l[place_i][::-1], len(l[place_i])-place_j-1, steps)
    return l
def up(l, num, steps, func):
    place_i, place_j=mainfuncs.find(l, num)
    p=[]
    for i_index in range(len(l)):
        p.append(l[i_index][place_j])
    p=func(p, place_i, steps)
    for index, p_value in enumerate(p):
        l[index][place_j]=p_value
    return l
def down(l, num, steps, func):
    place_i, place_j=mainfuncs.find(l, num)
    p_reverse=[]
    for i_index in range(len(l)):
        p_reverse.append(l[i_index][place_j])
    p_reverse=p_reverse[::-1]
    p_reverse=func(p_reverse, len(p_reverse)-place_i-1, steps)
    for index, p_value in enumerate(p_reverse[::-1]):
        l[index][place_j]=p_value
    return l
def upleft(l, num, steps, func):
    place_i, place_j=mainfuncs.find(l, num)
    p=[]
    index=0
    while True:
        if place_i*place_j==0:
            break
        place_i-=1
        place_j-=1
        index+=1
    i, j=place_i, place_j
    while True:
        try:
            p.append(l[place_i][place_j])
            place_i+=1
            place_j+=1
        except:
            break
    p=func(p, index, steps)
    for value in p:
        l[i][j]=value
        i+=1
        j+=1
    return l
def downright(l, num, steps, func):
    place_i, place_j=mainfuncs.find(l, num)
    p=[]
    index=0
    while True:
        if place_i*place_j==0:
            break
        place_i-=1
        place_j-=1
        index+=1
    i, j=place_i, place_j
    while True:
        try:
            p.append(l[place_i][place_j])
            place_i+=1
            place_j+=1
        except:
            break
    p=func(p[::-1], len(p)-1-index, steps)[::-1]
    for value in p:
        l[i][j]=value
        i+=1
        j+=1
    return l
def downleft(l, num, steps, func):
    place_i, place_j=mainfuncs.find(l, num)
    p=[]
    index=0
    while True:
        if not (0<place_i<len(l)-1 and 0<place_j<len(l[0])-1):
            break
        place_i+=1
        place_j-=1
        index+=1
    i, j=place_i, place_j
    while True:
        try:
            p.append(l[place_i][place_j])
            place_i-=1
            place_j+=1
        except:
            break
    p=func(p, index, steps)
    for value in p:
        l[i][j]=value
        i-=1
        j+=1
    return l
def upright(l, num, steps, func):
    place_i, place_j=mainfuncs.find(l, num)
    p=[]
    index=0
    while True:
        if not (0<place_i<len(l)-1 and 0<place_j<len(l[0])-1):
            break
        place_i-=1
        place_j+=1
        index+=1
    i, j=place_i, place_j
    while True:
        try:
            p.append(l[place_i][place_j])
            place_i+=1
            place_j-=1
        except:
            break
    p=func(p, index, steps)
    for value in p:
        l[i][j]=value
        i+=1
        j-=1
    return l
