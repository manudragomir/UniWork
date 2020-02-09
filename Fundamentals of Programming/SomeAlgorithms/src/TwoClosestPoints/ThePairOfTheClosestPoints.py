from cmath import sqrt


def Read():
    list = []
    n = int(input("n = "))
    
    for i in range(n):
        print("perechea e: ")
        x = float(input("x: "))
        y = float(input("y: "))
        list.append((x,y))
        
    return (n,list)       


def CalcDistance(Point1, Point2):
    return sqrt( (Point1[0] - Point2[0]) * (Point1[0] - Point2[0]) + (Point1[1] - Point2[1]) * (Point1[1] - Point2[1]) )

def ClosestPoints(list, left, right, n):
    
    if right - left == 1:
        dist = CalcDistance(list[left], list[right])
        return dist
    
    elif right - left == 2:
        dist1 = CalcDistance(list[left], list[left+1])
        dist2 = CalcDistance(list[left+1], list[right])
        dist3 = CalcDistance(list[left], list[right])
        return min(dist1,dist2,dist3)
    
    mid = (left + right) // 2
    xStrip = list[mid][0]
    
    Strip = []
    dist1 = ClosestPoints(list, left, mid, n)
    dist2 = ClosestPoints(list, mid, right, n)
    
    dmin = min(dist1,dist2)
    
    for i in range(n):
        if(abs(xStrip - list[i][0]) < dmin)
            Strip.append(list[i])
            
    Strip = sorted(Strip, key = lambda x: x[1])
    
    for i in range(n)
        for j in range(8)
            if CalcDistance(list[i], list[j]) < dmin
                dmin = CalcDistance(list[i], list[j])

def run():
    y = Read()
    
    n = y[0]
    list = y[1]
    
    list = sorted(list)
    
    dist = ClosestPoints(list, 1, n, n)
    
run()