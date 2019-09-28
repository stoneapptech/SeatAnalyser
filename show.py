import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from sys import argv
if len(argv)!=2:
    print("please run this program with the given format:\npython show.py [number to show]")
    exit(1)
def read(filename):
    with open(filename) as f:
        s=f.readline().split()
    for index, i in enumerate(s):
        s[index]=int(i)
    return np.array(s)
fig=plt.figure()
x=np.arange(6)
y=np.arange(5,-1,-1)
x, y=np.meshgrid(x, y)
x, y=x.ravel(), y.ravel()
width=depth=0.5
bottom=np.zeros_like(x)
axs=[]
for index, mode in enumerate(['rand', 'swap', 'push', 'inst']):
    top=read(argv[1]+'_'+mode+'.txt')
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
print('sum:',np.sum(top))
plt.show()
