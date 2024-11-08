import random

# Fixar la seed per garantir números aleatoris constants
random.seed(12345)

# Generar números aleatoris en el rang entre 0 i 10.000.000.000
for _ in range(1000000000):
    print(random.randint(0, 10000000))
