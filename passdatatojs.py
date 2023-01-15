"""
This code is the python side of a two-part script that allows data to be passed between python and js scripts.
I copied this code from the following YouTube video: https://www.youtube.com/watch?v=lSAFVMaaH-w.
Check out that link if you want to understand how this code works.
Made by Apes in Capes
"""

import sys
import json
import ast # abstract syntax tree

dataToPassBack = 'send this to node process'

# dict
input = ast.literal_eval(sys.argv[1])
output = input
output['data_returned'] = dataToPassBack
print(json.dumps(output))

sys.stdout.flush()