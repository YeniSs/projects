from back.Instruction import Instruction


class CoinFlipInstruction(Instruction):
    def view(self):
        cursor, connection = super().connect_to_database()
        cursor.execute("SELECT content FROM Instructions WHERE instructionName = 'CoinFlipInstruction'")
        result = cursor.fetchall()
        return result
