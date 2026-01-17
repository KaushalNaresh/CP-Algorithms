from typing import List

class Row:

    def __init__(self, id, name, age):
        self.id = id
        self.name = name
        self.age = age
    
    def get(self, column_name):

        if column_name == "id":
            return self.id
        if column_name == "name":
            return self.name
        if column_name == "age":
            return self.age


class Table:

    def __init__(self):
        self.rows: List[Row] = []
    
    def addRows(self, rows):

        for row in rows:
            self.rows.append(row)

class Database:

    def __init__(self):
        self.users = Table()

    def insert(self, table_name: str, row: Row) -> bool:

        if table_name == "users":
            self.users.addRows([row])
            return True
    
    def select(self, table_name, columns, where_condns):
        ans = []

        if table_name == "users":

            if not where_condns:
                for row in self.users.rows:
                    curr_row = []
                    for column in columns:
                        curr_row.append(row.get(column))
                    ans.append(curr_row)
            else:
                for row in self.users.rows:
                    curr_row = []
                    valid = True
                    for condn in where_condns:
                        col_name, op, val = condn.split(" ")

                        if valid and op == "=":
                            if row.get(col_name) != val:
                                valid = False
                        if  valid and op == "<":
                            if row.get(col_name) >= int(val):
                                valid = False
                        if  valid and op == ">":
                            if row.get(col_name) <= int(val):
                                valid = False

                    if valid:
                        for column in columns:
                            curr_row.append(row.get(column))
                        ans.append(curr_row)

            return ans
        
database = Database()
database.insert("users", Row(1, "Alice", 29))
database.insert("users", Row(2, "Max", 25))

print(database.select("users", ["id", "age", "name"], ["age > 20"]))
