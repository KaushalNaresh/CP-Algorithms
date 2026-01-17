class Formula:
    def __init__(self, cells, val):
        self.cells = cells
        self.val = val

class Excel:
    def __init__(self, H, W):
        self.H = H
        self.W = (ord(W) - ord('A'))+1

        self.formulas = [[None for _ in range(self.W)] for _ in range(self.H)]

        self.stack = []

    def get(self, r, c):

        rIndex = r-1
        cIndex = ord(c) - ord('A')

        if self.formulas[rIndex][cIndex] is None:
            return 0
        return self.formulas[rIndex][cIndex].val
    
    def set(self, r, c, v):

        rIndex = r-1
        cIndex = ord(c) - ord('A')

        self.formulas[rIndex][cIndex] = Formula({}, v)

        self.topologicalSort(rIndex, cIndex)
        self.execute_stack()

    def sum(self, r, c, strs):

        rIndex = r - 1
        cIndex = ord(c) - ord('A')

        cells = self.convert(strs)

        summ = self.calculate_sum(rIndex, cIndex, cells)

        self.set(r, c, summ)

        self.formulas[rIndex][cIndex] = Formula(cells, summ)

        return summ

    def convert(self, strs): # strs = ["A1", "B1:C2"]

        res = {}

        for st in strs:
            if ':' not in st:
                res[st] = res.get(st, 0) + 1
            else:
                left, right = res.split(":")

                startCol = left[0]
                startRow = int(left[1:])

                endCol = right[0]
                endRow = int(right[1])

                for rowNum in range(startRow, endRow+1):
                    for colOrd in range(ord(startCol), ord(endCol) + 1):
                        cell_name = chr(colOrd) + str(rowNum)
                        res[cell_name] = res.get(cell_name, 0) + 1

        return res
    
    def calculate_sum(self, r, c, cells):

        total = 0

        for cell_name, count in cells.items():
            cc = ord(cell_name[0]) - ord('A')
            rr = cell_name[1]-1

            refVal = 0
            if self.formulas[rr][cc] is not None:
                refVal = self.formulas[rr][cc].val
            total += refVal * count

        self.formulas[r][c] = Formula(cells, total)
        return total
    
    def topologicalSort(self, r, c):

        cellName = chr(ord('A') + c) + str(r+1)

        for i in range(self.H):
            for j in range(self.W):
                formula = self.Formulas[i][j]
                if formula is not None:
                    if cellName in formula.cells:
                        self.topologicalSort(i, j)

        self.stack.append((r, c))

    def execute_stack(self):

        while self.stack:
            r, c = self.stack.pop()
            formula = self.formulas[r][c]
            if formula is not None and len(formula.cells) > 0:
                self.calculate_sum(r, c, formula.cells)






## LAZY

class Excel:

    def __init__(self, height: int, width: str):
        self.height = height
        self.width = ord(width) - ord('A')

        self.references = [[None for _ in range(self.width+1)] for _ in range(self.height)]
        self.values = [[0 for _ in range(self.width+1)] for _ in range(self.height)]
        

    def set(self, row: int, column: str, val: int) -> None:

        cc = ord(column) - ord('A')
        self.values[row-1][cc] = val
        self.references[row-1][cc] = None
        

    def get(self, row: int, column: str) -> int:

        cc = ord(column) - ord('A')
        if not self.references[row-1][cc]:
            return self.values[row-1][cc]
        
        total = 0
        for ref in self.references[row-1][cc]:
            total += self.get(int(ref[1:]), ref[0])

        return total
        

    def sum(self, row: int, column: str, numbers: List[str]) -> int:
        
        cells = []
        summ = 0

        for number in numbers:
            if ":" in number:
                strt_cell, end_cell = number.split(":")
                strt_rr = int(strt_cell[1:])
                end_rr = int(end_cell[1:])
                strt_cc = ord(strt_cell[0]) 
                end_cc = ord(end_cell[0]) 

                for i in range(strt_rr-1, end_rr):
                    for j in range(strt_cc, end_cc+1):
                        cell_name = ""+chr(j)+str(i+1)
                        cells.append(cell_name)
                        summ += self.get(i+1, chr(j))
            else:
                rr = int(number[1:])
                cc = number[0]
                summ += self.get(rr, cc)
                cell_name = cc+str(rr)
                cells.append(cell_name)
        
        self.references[row-1][ord(column)-ord('A')] = cells
        self.values[row-1][ord(column)-ord('A')] = summ

        return summ









## EAGER

class Formula:
    def __init__(self, cells, val):
        """
        cells: dict mapping 'A1', 'B2', etc. -> integer count (how many times referenced)
        val:   computed integer value of this cell
        """
        self.cells = cells
        self.val = val

class Excel:
    def __init__(self, H, W):
        """
        H: number of rows (1..H)
        W: rightmost column character, e.g. 'A'..'Z'
           We'll store Formulas in a 2D list [H][numCols], 0-based indexing internally.
        """
        # Convert W to a 0-based width. E.g. if W='C', columns are 'A','B','C' => 3 wide
        self.H = H
        self.W = (ord(W) - ord('A')) + 1  
        
        # 2D array of Formulas. Each entry is either None or a Formula object
        self.Formulas = [[None for _ in range(self.W)] for _ in range(self.H)]
        
        # We'll use a simple Python list as our "stack"
        self.stack = []

    def get(self, r, c):
        """
        Return the current value of cell (r, c).
        r is 1-based row index, c is a character column label.
        """
        rIndex = r - 1
        cIndex = ord(c) - ord('A')
        if self.Formulas[rIndex][cIndex] is None:
            return 0
        return self.Formulas[rIndex][cIndex].val

    def set(self, r, c, v):
        """
        Set cell (r,c) to a direct integer value 'v', with no references.
        Then do topological sort + execute_stack to recalc any dependent cells.
        """
        rIndex = r - 1
        cIndex = ord(c) - ord('A')
        
        # Make a direct formula (empty references, val = v)
        self.Formulas[rIndex][cIndex] = Formula({}, v)
        
        # Rebuild topological order from (rIndex, cIndex) outward
        self.topologicalSort(rIndex, cIndex)
        self.execute_stack()

    def sum(self, r, c, strs):
        """
        Set cell (r,c) to be the SUM of the references in 'strs'.
        'strs' might look like ["A1","A1","A2:B3"] etc.
        """
        rIndex = r - 1
        cIndex = ord(c) - ord('A')
        
        # Convert the references (which may have ranges) into a dict {cellName -> count}
        cells = self.convert(strs)
        
        # Calculate the sum
        summ = self.calculate_sum(rIndex, cIndex, cells)
        
        # We call set(...) to trigger topological sort + stack execution
        # so everything that depends on (r,c) also gets updated.
        self.set(r, c, summ)
        
        # Overwrite the formula again to preserve the references (because set() used an empty dict).
        self.Formulas[rIndex][cIndex] = Formula(cells, summ)
        
        return summ

    def topologicalSort(self, r, c):
        """
        Recursively visit all cells that reference (r,c), then push (r,c) on stack.
        This is the same logic as the Java code that does a full scan to see who references this cell.
        """
        # The 'name' of cell (r,c) is e.g. 'A1' if c=0 and r=0.
        cellName = chr(ord('A') + c) + str(r + 1)
        
        # Check all cells in the spreadsheet
        for i in range(self.H):
            for j in range(self.W):
                formula = self.Formulas[i][j]
                if formula is not None:
                    # If that cell references the cellName
                    if cellName in formula.cells:
                        # Recursively topologicalSort that cell first
                        self.topologicalSort(i, j)
        
        # Then push (r,c) on the stack
        self.stack.append((r, c))

    def execute_stack(self):
        """
        Pop from the stack and recalculate the cell's value if it has references.
        """
        while self.stack:
            r, c = self.stack.pop()
            formula = self.Formulas[r][c]
            if formula is not None and len(formula.cells) > 0:
                self.calculate_sum(r, c, formula.cells)

    def convert(self, strs):
        """
        Convert an array like ["A1", "B1:C2"] into a dict of { "A1": count, "B1": count, etc. }.
        """
        res = {}
        for st in strs:
            if ':' not in st:
                # single cell, e.g. "A1"
                res[st] = res.get(st, 0) + 1
            else:
                # range, e.g. "A1:B2"
                left, right = st.split(':')
                
                # Parse left cell e.g. "A1"
                startCol = left[0]              # e.g. 'A'
                startRow = int(left[1:])        # e.g. 1
                # Parse right cell e.g. "B2"
                endCol   = right[0]
                endRow   = int(right[1:])
                
                for rowNum in range(startRow, endRow + 1):
                    for colOrd in range(ord(startCol), ord(endCol) + 1):
                        cellName = chr(colOrd) + str(rowNum)
                        res[cellName] = res.get(cellName, 0) + 1
        return res

    def calculate_sum(self, r, c, cells):
        """
        Recompute the sum of references in 'cells' for cell (r,c).
        Then store that new sum in Formulas[r][c].val.
        """
        total = 0
        for cellName, count in cells.items():
            colChar = cellName[0]         # e.g. 'A'
            rowNum = int(cellName[1:])    # e.g. 3
            rr = rowNum - 1
            cc = ord(colChar) - ord('A')
            
            # If that referenced cell is null, treat as 0
            refVal = 0
            if self.Formulas[rr][cc] is not None:
                refVal = self.Formulas[rr][cc].val
            total += refVal * count
        
        # Update (r,c) with the new sum
        self.Formulas[r][c] = Formula(cells, total)
        return total
