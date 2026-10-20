import math

TABLE_LEN = 3000
MID_CODE = 1861
HIGH_CODE = 3722

codes = []
for i in range(TABLE_LEN):
    code = round(MID_CODE + MID_CODE * math.sin(2 * math.pi * i / TABLE_LEN))
    code = max(0, min(HIGH_CODE, code))
    codes.append(code)

for i in range(0, TABLE_LEN, 10):
    row = ", ".join(str(c) for c in codes[i:i + 10])
    print(f"    {row},")
