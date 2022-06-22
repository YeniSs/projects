from back.Instruction import Instruction


class RouletteInstruction(Instruction):
    def view(self):
        cursor, connection = super().connect_to_database()
        cursor.execute("SELECT content FROM Instructions WHERE instructionName = 'RouletteInstruction'")
        result = cursor.fetchall()
        return result
