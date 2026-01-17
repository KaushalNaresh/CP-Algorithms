import heapq
from enum import Enum
from typing import List

class ElevatorState(Enum):
    IDLE = "IDLE"
    UP = "UP"
    DOWN = "DOWN"

class Request:

    def __init__(self, sourceFloor, destFloor, requestType):
        self.sourceFloor = sourceFloor
        self.destFloor = destFloor

    def __hash__(self):
        return hash((self.sourceFloor, self.destFloor))

    def __eq__(self, other):
        return isinstance(other) == Request and other.sourceFloor == self.sourceFloor and other.destFloor == self.destFloor

class Elevator:

    def __init__(self, maxLimit: int):
        self.currState = ElevatorState.IDLE
        self.currFloor = 0
        self.passengerLimit = maxLimit
        self.countOfPassengers = 0
        self.downReuqests = []  # max Heap
        self.upRequests = []  # min Heap 
        self.waitingQueue = set(Request)

    def addExternalRequest(self, request: Request):
        self.waitingQueue.add(request)


    def addInternalRequest(self, request: Request):

        if self.countOfPassengers > self.passengerLimit:
            print("Elevator Full")

        if self.currState == ElevatorState.UP:
            if request.destFloor >= self.currFloor:
                heapq.heappush(self.upRequests, [request.destFloor, request])
            else:
                heapq.heappush(self.downReuqests, [-request.destFloor, request])
        elif self.currState == ElevatorState.DOWN:
            if request.destFloor <= self.currFloor:
                heapq.heappush(self.downReuqests, [-request.destFloor, request])
            else:
                heapq.heappush(self.upRequests, [request.destFloor, request])
        elif self.currState == ElevatorState.IDLE:
            if request.destFloor >= self.currFloor:
                self.currState = ElevatorState.UP
                heapq.heappush(self.upRequests, [request.destFloor, request])
            else:
                self.currState = ElevatorState.DOWN
                heapq.heappush(self.downReuqests, [-request.destFloor, request])

    def boardPassengers(self):

        for waitRequest in self.waitingQueue:
            if waitRequest.sourceFloor == self.currFloor and self.countOfPassengers < self.passengerLimit:
                self.addInternalRequest(waitRequest)
                self.waitingQueue.remove(waitRequest)
                self.countOfPassengers += 1

    def deboardPassengers(self):

        if self.currState == ElevatorState.UP:
            if self.currFloor == -self.minHeap[0]:
                heapq.heappop(self.minHeap)
                self.countOfPassengers -= 1
                if not self.minHeap and not self.waitingQueue and self.maxHeap:
                    self.currState = ElevatorState.DOWN
        else:
            if self.currFloor == -self.maxHeap[0]:
                heapq.heappop(self.maxHeap)
                self.countOfPassengers -= 1
                if not self.maxHeap:
                    self.currState = "UP"


    def move(self):

        while self.waitingQueue or self.upRequests or self.downReuqests:
            self.boardPassengers()
            self.deboardPassengers()
            if self.currState == ElevatorState.UP:
                self.currFloor += 1
            elif self.currState == ElevatorState.DOWN:
                self.currFloor -= 1





"""
1. Multiple elevators
2. Internal request
3. limit
"""

class Request:
    def __init__(self, floor: int):
        self.floor = floor

class ElevatorState(Enum):
    IDLE = "IDLE"
    MOVING = "MOVING"

class ElevatorDirection(Enum):
    UP = "UP"
    DOWN = "DOWN"
    IDLE = "IDLE"


class Elevator:

    def __init__(self, idx: int):
        self.idx = idx
        self.currState = ElevatorState.IDLE
        self.currFloor = 0
        self.direction = ElevatorDirection.IDLE
        self.requests = []

    def addRequest(self, request):
        self.requests.append(request)
        self.processRequests()

    def processRequests(self):
        while self.requests:
            currRequest = self.requests.pop(0)
            self.moveToFloor(currRequest.floor)

    def moveToFloor(self, floor):

        if self.currFloor > floor:
            self.direction = ElevatorDirection.DOWN
        elif self.currFloor < floor:
            self.direction = ElevatorDirection.UP
        else:
            print(f"We are alrady at floor {floor}")
            self.direction = ElevatorDirection.IDLE
            return

        while self.currFloor != floor:
            self.currFloor += 1 if self.direction == ElevatorDirection.UP else -1
        
        self.currState = ElevatorState.IDLE
        self.direction = ElevatorDirection.IDLE
        return



class ElevatorController:

    def __init__(self, totalElevators):
        self.elevators = [Elevator(i) for i in range(totalElevators)]
    
    def getElevator(self, floor):
        
        nearestElevator = self.getNearestElevator(floor)
        if nearestElevator:
            nearestElevator.addRequest(Request(floor))

    def getNearestElevator(self, floor):

        self.idleElevators = [elevator for elevator in self.elevators if elevator.currState == ElevatorState.IDLE]
        if self.idleElevators:
            sorted(self.idleElevators, lambda x: abs(x.currFloor - floor))
            return self.idleElevators[0]

        return self.elevators[0] ## Fallback: return the first elevator
    

