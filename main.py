import matplotlib.pyplot as plt
import numpy as np;


#Numero de colisões 

# Y = quantidade média de colisões 

# X = quantidade de string e M

#Tempo de pesquisa 

#Y = tempo médio de pesquisa

#X = quantidade string's e M

quant_string = ("100","1000","10000")

colisionByM = {
    
    '31' : (18.35,18.43,14.98),
    '79' : (38.79, 48.83,47.50),
    '151' : (189.95, 195.82, 217.19)      
}



x = np.arange(len(quant_string))
width = 0.25
multiplier = 0

fig, ax = plt.subplots(layout = 'constrained')


for attribute, measurement in 