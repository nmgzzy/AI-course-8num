# -*- coding: utf-8 -*-
#有序搜索类

class HeuristicSearch():
    
    def __init__(self, original_node, target_node):
        self.original_node = original_node
        self.target_node = target_node
        self.open = []
        self.closed = []
        #[0节点编号，1父节点编号，2操作符，3-11状态*9，12深度，13估价，14总代价]
        
    def get_cost(self, node):
        cnt = 0
        for i in range(0,9):
            if node[i] != self.target_node[i] and node[i] != 0:
                cnt+=1
        return cnt, cnt+node[9]
            
    def is_target(self, node):
        if node == self.target_node:
            return True
        else:
            return False
    
    def get_next_node(self):
        fmin = self.open[0][14]
        fmin_node = []
        for node in self.open:
            if fmin > node[14]:
                fmin = node[14]
        for node in self.open:
            if fmin == node[14]:
                fmin_node.append(node)
        for next_node in fmin_node:
            if self.is_target(next_node[3:12]):
                return next_node, True
        return fmin_node[0], False
    
    def find_index(self, node):
        for i in range(0,9):
            if node[i]==0:
                return i
           
    def create_node(self, direction, index):
        next_node = self.closed[-1][:]
        next_node[0] = 0
        next_node[1] = self.closed[-1][0]
        next_node[2] = direction
        next_node[12] = self.closed[-1][12] + 1
        if direction == 'U':
            next_node[index],next_node[index-3] = next_node[index-3],next_node[index]
        elif direction == 'L':
            next_node[index],next_node[index-1] = next_node[index-1],next_node[index]
        elif direction == 'D':
            next_node[index],next_node[index+3] = next_node[index+3],next_node[index]
        elif direction == 'R':
            next_node[index],next_node[index+1] = next_node[index+1],next_node[index]
            
        next_node[13],next_node[14] = self.get_cost(next_node[3:13])
        return next_node
        
    def judge_son(self, son):
        for o in self.open:
            if o[3:13] == son:
                return 'o', o
        for c in self.closed:
            if c[3:13] == son:
                return 'c', c
        return 'n', son
    
    def expend_node(self, node): 
        index = self.find_index(node[3:12])
        flag = {'L':1, 'U':1, 'R':1, 'D':1}
        if index == 0 or index == 1 or index == 2 or node[2] == 'D':
            flag['U'] = 0
        if index == 0 or index == 3 or index == 6 or node[2] == 'R':
            flag['L'] = 0
        if index == 6 or index == 7 or index == 8 or node[2] == 'U':
            flag['D'] = 0
        if index == 2 or index == 5 or index == 8 or node[2] == 'L':
            flag['R'] = 0

        for key,val in flag.items():
            if val == 1:
                son = self.create_node(key, index+3)
                location, hist_node = self.judge_son(son[3:13])
                if location == 'o':
                    if son[-1] < hist_node[-1]:
                        self.open.remove(hist_node)
                        self.open.append(son)
                elif location == 'c':
                    if son[-1] < hist_node[-1]:
                        self.closed.remove(hist_node)
                        self.open.append(son)
                else:
                    self.open.append(son)
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        