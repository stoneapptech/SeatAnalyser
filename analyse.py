from sys import argv
try:
    number,times=int(argv[1]),int(argv[2])
except:
    print("""Please input with the correct format:
    python analyse.py [number to find] [times to analyse]""")
    exit(1)
import mainfuncs
import execute
import numpy as np
import matplotlib.pyplot as plt
from copy import deepcopy as dp
from mpl_toolkits.mplot3d import Axes3D
import funcs
from time import time
from math import floor
now = time()
poss_rand=np.zeros((6,6))
poss_swap=np.zeros((6,6))
poss_push=np.zeros((6,6))
poss_inst=np.zeros((6,6))
poss=[poss_rand, poss_swap, poss_push, poss_inst]
reqs=mainfuncs.loadfile('requirements.txt')
for _ in range(times):
    execute.funcs.mainfuncs.shuffle(reqs)
    swap=mainfuncs.create()
    push=dp(swap)
    inst=dp(swap)
    place_i, place_j=mainfuncs.find(swap, number)
    poss_rand[place_i][place_j]+=1
    swap=execute.execute(swap, reqs, funcs.swap)
    push=execute.execute(push, reqs, funcs.push)
    inst=execute.execute(inst, reqs, funcs.inst)
    place_i, place_j=mainfuncs.find(swap, number)
    poss_swap[place_i][place_j]+=1
    place_i, place_j=mainfuncs.find(inst, number)
    poss_inst[place_i][place_j]+=1
    place_i, place_j=mainfuncs.find(push, number)
    poss_push[place_i][place_j]+=1
fig=plt.figure()
x=np.arange(6)
y=np.arange(5,-1,-1)
x, y=np.meshgrid(x, y)
x, y=x.ravel(), y.ravel()
width=depth=0.5
bottom=np.zeros_like(x)
axs=[]
print('data generated this time:')
for index, mode in enumerate(['rand', 'swap', 'push', 'inst']):
    try:
        old=open(str(number)+'_'+mode+'.txt').read().split()
        for i in range(len(old)):
            old[i]=int(old[i])
        old=np.array(old)
    except:
        old=np.zeros(36, dtype=int)
    top=poss[index].ravel().astype(int)+old
    if mode!='rand':
        r=[]
        perc=np.percentile(top, [25,50,85])
        for i in top:
            if i>=perc[2]:
                r.append('#E50500')
            elif i>=perc[1]:
                r.append('#EA8800')
            elif i>=perc[0]:
                r.append('#50FA4D')
            else:
                r.append('#0400E6')
    else:
        r=None
    axs.append(fig.add_subplot(220+index+1, projection='3d'))
    axs[index].bar3d(x, y, bottom, width, depth, top, shade=True, color=r)
    axs[index].set_title(mode)
    with open(str(number)+'_'+mode+'.txt', 'w') as file:
        print(mode+':', end='')
        for i in top:
            print(i, end=' ')
            file.write(str(i))
            file.write(' ')
        print()
print('execution time:',floor(time()-now), 'secs')
plt.show()
