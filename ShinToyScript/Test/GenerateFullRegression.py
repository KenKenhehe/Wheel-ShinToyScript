from typing import Text
import os
file_to_igonre = ['GenerateFullRegression.py',
                  'Grammar.txt', 'Regression.sts']
full_regression_output = ''
for file_name in os.listdir(os.getcwd()):
    if file_name not in file_to_igonre:
        with open(os.path.join(os.getcwd(), file_name), 'r') as f:
            full_regression_output = full_regression_output + "\n" + f.read()

with open("Regression.sts", 'w') as fr:
    fr.flush()
    fr.write(full_regression_output)
    fr.close()
