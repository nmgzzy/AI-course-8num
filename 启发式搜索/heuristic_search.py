# -*- coding: utf-8 -*-
import random
import time
from HS import HeuristicSearch

def main():
    original_node = [0,2,4,1,5,3,8,7,6]
    target_node = [1,2,3,8,0,4,7,6,5]
    
    t, original_node = input_node(original_node, target_node[:])
    if t == False:
        print('input error')
    else:
        start = time.time()
        hs = HeuristicSearch(original_node, target_node)
        cost, f = hs.get_cost(original_node+[0])
        if cost == 0:
            print('the original node is equal to target node.')
            
        hs.open.append([0,0,0] + original_node + [0,cost,f])
        
        while(True):
            if len(hs.open) == 0:
                print('not find')
                break
            
            next_node, isfind = hs.get_next_node()
            
            hs.open.remove(next_node)
            try:
                next_node[0] = hs.closed[-1][0] + 1
            except:
                next_node[0] = 0
            hs.closed.append(next_node)
            
            if isfind:
                stop = time.time()
                print_solution(hs.open[:], hs.closed[:])
                print('\nlen open:',len(hs.open))
                print('len closed:',len(hs.closed))
                print('\nrun time:',stop-start)
                break
            
            hs.expend_node(next_node)
        

def print_solution(listo, listc):
    print('find solution!')
    print('---------- open: ----------')
    for i in listo:
        print('{:5d}{:5d}  {}  |{:3d}{:3d}{:3d}{:3d}{:3d}{:3d}{:3d}{:3d}{:3d}  |{:4d}{:4d}{:4d}'\
              .format(i[0],i[1],i[2], i[3],i[4],i[5],i[6],i[7],i[8],i[9],i[10],i[11], i[12],i[13],i[14]))
    print('--------- closed: ---------')
    for i in listc:
        print('{:5d}{:5d}  {}  |{:3d}{:3d}{:3d}{:3d}{:3d}{:3d}{:3d}{:3d}{:3d}  |{:4d}{:4d}{:4d}'\
              .format(i[0],i[1],i[2], i[3],i[4],i[5],i[6],i[7],i[8],i[9],i[10],i[11], i[12],i[13],i[14]))
    print('--------- process: --------')
    listc.reverse()
    sln = []
    sln.append(listc[0])
    i = 0
    while(listc[i][0] != 0):
        father_point = listc[i][1]
        while(father_point != listc[i][0]):
            i += 1
        sln.append(listc[i])
    sln.reverse()
    for i in sln:
        if i[2] != 0:
            print('{}\n{:3d}{:3d}{:3d}\n{:3d}{:3d}{:3d}\n{:3d}{:3d}{:3d}'\
                  .format(i[2],i[3],i[4],i[5],i[6],i[7],i[8],i[9],i[10],i[11]))
        else:
            print('{:3d}{:3d}{:3d}\n{:3d}{:3d}{:3d}\n{:3d}{:3d}{:3d}'\
                  .format(i[3],i[4],i[5],i[6],i[7],i[8],i[9],i[10],i[11]))
  
    
def findIndex(node):
    for i in range(0,9):
        if node[i]==0:
            return i

def generate_original_node(target_node, step):
    original_node = target_node
    last_step = 0
    random.seed()
    for i in range(step):
        index = findIndex(original_node)
        flag = {1:1, 2:1, 3:1, 4:1}
        if index == 0 or index == 1 or index == 2 or last_step == 4:
            flag[2] = 0
        if index == 0 or index == 3 or index == 6 or last_step == 3:
            flag[1] = 0
        if index == 6 or index == 7 or index == 8 or last_step == 2:
            flag[4] = 0
        if index == 2 or index == 5 or index == 8 or last_step == 1:
            flag[3] = 0
        r = random.randint(1,4)
        while(flag[r] == 0):
            r = random.randint(1,4)
        if r == 2:
            original_node[index],original_node[index-3] = original_node[index-3],original_node[index]
        elif r == 1:
            original_node[index],original_node[index-1] = original_node[index-1],original_node[index]
        elif r == 4:
            original_node[index],original_node[index+3] = original_node[index+3],original_node[index]
        elif r == 3:
            original_node[index],original_node[index+1] = original_node[index+1],original_node[index]
        last_step = r
    return original_node
        

def input_node(original_node, target_node):
    way = int(input('please choose input way \n 1 --- automatic generation;\n 2 --- user input;\n other --- default: '))
    if way == 1:
        step = int(input( "please input step number (1~20) : "))
        if step>0 and step <=20:
            original_node = generate_original_node(target_node, step)
            return True, original_node
        else:
            return False, []
    elif way == 2:
        print('please input original_node:')
        for i in range(1,10):
            try:
                original_node[i-1] = int(input('please input number {}: '.format(i)))
            except:
                return False, []
        if(sorted(original_node) == [0,1,2,3,4,5,6,7,8]):
            return True, original_node
        else:
            return False, []
    else:
        return True, original_node


main()

