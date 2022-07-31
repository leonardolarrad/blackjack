import sys
import os

dir = sys.argv[1]

for filename in os.listdir(dir):
    if filename.endswith('.png'):     
        path = dir + '/' + filename
                
        if filename.lower().startswith('a'):
            os.rename(path, dir + '/1' + filename.lower()[1:])
        elif filename.lower().startswith('t'):
            os.rename(path, dir + '/10' + filename.lower()[1:])
        elif filename.lower().startswith('j'):
            os.rename(path, dir + '/11' + filename.lower()[1:])
        elif filename.lower().startswith('q'):
            os.rename(path, dir + '/12' + filename.lower()[1:])
        elif filename.lower().startswith('k'):
            os.rename(path, dir + '/13' + filename.lower()[1:])
        else:
            os.rename(path, path.lower())
    

