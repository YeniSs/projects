from back.Instruction import Instruction


class SlotsInstruction(Instruction):
    def view(self):
        cursor, connection = super().connect_to_database()
        cursor.execute("SELECT content FROM Instructions WHERE instructionName = 'SlotsInstruction'")
        result = cursor.fetchall()
        return result
