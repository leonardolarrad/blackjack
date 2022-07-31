import os

# rename all 52-cards in folder to numerbersuit.png 
# example:
# 1B.png -> 1b.png
# 2B.png -> 2b.png
# set lowercase names for all cards
# change J, Q, K to 10, 11, 12

for filename in os.listdir('.'):
    if filename.endswith('.png'):
        os.rename(filename, filename.lower())

        print(filename)
        print(filename.lower())
        print('\n')

        # rename J, Q, K to 10, 11, 12
        # rename A to 1
        if filename.startswith('a'):
            os.rename(filename, '1' + filename[1:])

        if filename.startswith('j'):
            os.rename(filename, '10' + filename[1:])
        elif filename.startswith('q'):
            os.rename(filename, '11' + filename[1:])
        elif filename.startswith('k'):
            os.rename(filename, '12' + filename[1:])