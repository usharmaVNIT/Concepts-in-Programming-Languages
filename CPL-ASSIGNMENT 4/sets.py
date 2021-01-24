
#
#  sets.py
#  Created by Official on 21/05/20.
#  Copyright © 2020 Official. All rights reserved.
#

class SetDataStructure:
    def __init__(self,contents):
        self.items = [None]*20
        self.numItems = 0

        for item in contents:
            self.add(item)
    def __add(item,items):
        # Note already len(items) is non-zero
        i = hash(item)%(len(items))
        location = -1
        l = len(items)
        while items[i] != None:
            if items[i] == item:
                return False

            if location < 0 and type(items[i]) == SetDataStructure.__FakeValue:
                location = i

            i = (i+1)%l
        if location < 0:
            location = i

        items[location] = item

        return True
    # We will make sure that the list will never be full and to do so we will
    # add the existing list into a new list

    def __rehash(oldList, newList):
        for x in oldList:
            if x != None and type(x) != SetDataStructure.__FakeValue:
                SetDataStructure.__add(x,newList)

        return newList

    def add(self,item):
        if SetDataStructure.__add(item,self.items):
            self.numItems+=1
            loadfactor = self.numItems / len(self.items)

            if loadfactor >=0.75:
                self.items = SetDataStructure.__rehash(self.items,[None]*2*len(self.items))
        else:
            print("Item Already Present In The SetDataStructure")
            

# This functions are for deleting the values
    class __FakeValue:
        # Note This is a placeholder for value therfore it doesnot contain any initialization
        def __init__(self):
            pass
        # This function is for equaliy check with other classes
        def __eq__(self,other):
            return False
    # This is a utility Function For Delete
    def __remove(item,items):
        i = hash(item) % len(items)

        while items[i] !=None:
            if items[i] == item:
                next_i = (i+1)%len(items)
                if items[next_i] == None:
                    items[i] = None
                else:
                    items[i] = SetDataStructure.__FakeValue()
                return True
            i = (i+1)%len(items)
        return False


    def remove(self,item):
        if SetDataStructure.__remove(item,self.items):
            self.numItems -=1
            # Now as we Did In the add function we Dynamically Shrink our Set List
            # Now you need to take care of the edge cases minimul length is to be of 20
            loadfactor = max(self.numItems,20)%len(self.items)
            if loadfactor <= 0.25:
                self.items = SetDataStructure.__add(self.items,[None]*len(self.items)//2)
        else:
            print("Item Not Present In The SetDataStructure")

    def __contains(item,items):
        i = hash(item)%len(items)
        while items[i] != None:
            if items[i] == item:
                return True
            i= (i+1)%len(items)
        # Here This Condition is valid as i am making sure that my list is never full(>=75%)
        return False

    def contains(self,item):
        return SetDataStructure.__contains(item,self.items)

    # Now To Check if it is empyty
    def isEmpty(self):
        if self.numItems == 0:
            return True
        return False

    # Now To Determine Size of Set
    def size(self):
        return self.numItems
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    # For Union Of 2 Sets
    def __union(list1,list2):
        fu = [None]*(len(list1)+len(list2))
        for ele in list1:
            if ele != None and type(ele) != SetDataStructure.__FakeValue:
                if SetDataStructure.__contains(ele,list2) == False:
                    SetDataStructure.__add(ele,fu)
        for ele in list2:
            if ele != None and type(ele) != SetDataStructure.__FakeValue:
                SetDataStructure.__add(ele,fu)

        return fu

    def union(self,new_set):
        if self.numItems == 0:
            return new_set.items
        elif new_set.numItems == 0:
            return self.items
        else:
            return SetDataStructure.__union(self.items,new_set.items)

#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    # For InterSection Of 2 Sets

    def __intersection(list1,list2):
        inter = [None]*min(len(list1),len(list2))
        for ele in list1:
            if ele != None and type(ele) != SetDataStructure.__FakeValue:
                if SetDataStructure.__contains(ele,list2):
                    SetDataStructure.__add(ele,inter)
        return inter

    def intersection(self,new_set):
        if self.numItems == 0 or new_set.numItems == 0:
            return []
        else:
            return SetDataStructure.__intersection(self.items,new_set.items)
        
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    # For Difference
    def __difference(list1,list2):
        l1=list1[:]
        l2=list2[:]
        rem = SetDataStructure.__intersection(list1,list2)
        for ele in rem:
            if ele != None and type(ele) != SetDataStructure.__FakeValue:
                SetDataStructure.__remove(ele,l1)
                SetDataStructure.__remove(ele,l2)
        return SetDataStructure.__union(l1,l2)

    def difference(self,new_set):
        return SetDataStructure.__difference(self.items,new_set.items)

#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    # For Subset

    def __subset(list1,list2):
        for ele in list2:
            if ele != None and type(ele) != SetDataStructure.__FakeValue:
                if SetDataStructure.__contains(ele,list1) == False:
                    return False
            return False

    def subset(self, new_set):
        return SetDataStructure.__subset(self.items,new_set.items)

    
    
        
