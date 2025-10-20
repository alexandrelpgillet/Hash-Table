import matplotlib.pyplot as plt
import numpy as np;
from matplotlib import rcParams


#Numero de colisões 

# Y = quantidade média de colisões 

# X = quantidade de string e M

#Tempo de pesquisa 

#Y = tempo médio de pesquisa

#X = quantidade string's e M

quant_string = ("100","1000","10000")

colisionByM = {
    
    '31' : (0.017970,0.010300,0.034970),
    '79' : (0.009550, 0.009590,0.020760),
    '151' : (0.009260, 0.010080, 0.016680)      
}


#100;31;0.017970;3.070968
#100;79;0.009550;0.882278
#100;151;0.009260;0.319205
#1000;31;0.010300;32.258064
#1000;79;0.009590;12.658228
#1000;151;0.010080;6.618543
#10000;31;0.034970;322.580658
#10000;79;0.020760;126.582275
#10000;151;0.016680;66.225166
#100000;31;0.335540;3225.806396
#00000;79;0.152230;1265.822754
#100000;151;0.092490;662.251648




# plotting parameters
rcParams.update({
    'figure.figsize': (10, 6),
    'font.size': 12,
})

x = np.arange(len(quant_string))
num_bars = len(colisionByM)
width = 0.8 / num_bars  # auto width so all bars fit nicely

fig, ax = plt.subplots(layout='constrained')

colors = plt.get_cmap('tab10').colors
multiplier = 0

for i, (attribute, measurement) in enumerate(colisionByM.items()):
    offset = (i - (num_bars - 1) / 2) * width
    rects = ax.bar(x + offset, measurement, width, label=f"M={attribute}", color=colors[i % len(colors)], edgecolor='black')
    ax.bar_label(rects, padding=3, fmt='%.2f')

ax.set_ylabel("Tempo médio de busca de um item na hash table (média)")
ax.set_title("Tempo em milissegundos")
# set xticks at the center of groups
ax.set_xticks(x)
ax.set_xticklabels(quant_string)
ax.set_xlabel("Quantidade de strings (N)")

ax.legend(loc='upper left', ncols=3, frameon=True)
ax.set_ylim(0, max(max(v) for v in colisionByM.values()) * 1.15)
ax.yaxis.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.show()
 