import matplotlib.pyplot as plt
import numpy as np
import csv

files = ['bubble_sort', 'selection_sort', 'insert_sort', 'stable_sort', 'sort']
dict_data = dict()
ops_data = dict()

for func_name in files:
    data = list(csv.reader(open(f"csv/time_{func_name}.csv")))
    swp_data = list(csv.reader(open(f"csv/{func_name}_affectations.csv")))
    cmp_data = list(csv.reader(open(f"csv/{func_name}_comparisons.csv")))
    dict_data[func_name] = data
    ops_data[func_name] = {"swp": swp_data, "cmp": cmp_data}
    plt.figure(figsize=(12, 6))
    x = [int(i) for i in data[0]]
    plt.plot(x, [float(i) if float(i) != 0 else 1 for i in data[1]], marker='o', label='ascendant')
    plt.plot(x, [float(i) if float(i) != 0 else 1 for i in data[2]], marker='o', label='descendant')
    plt.plot(x, [float(i) if float(i) != 0 else 1 for i in data[3]], marker='o', label='non-ordonné')
    plt.plot(x, [float(i) if float(i) != 0 else 1 for i in data[4]], marker='o', label='partiellement ordonné')

    plt.title(f'Temps d\'exécution de {func_name} en fonction de la taille de l\'entrée.')
    plt.ylabel('Temps [ms]')
    plt.xlabel('Taille de l\'entrée [nombre d\'éléments]')
    plt.yscale('log')
    plt.xscale('log')
    plt.grid(True)
    plt.legend()
    plt.savefig(f'time_{func_name}.svg')

cnt = 1
for t in ['ascendant', 'descendant', 'non-ordonné', 'partiellement ordonné']:
    plt.figure(figsize=(12, 6))
    for f in files:
        plt.plot([int(i) if int(i) != 0 else 1 for i in ops_data[f]['swp'][0]], [int(i) if int(i) != 0 else 1 for i in ops_data[f]['swp'][cnt]], marker='o',
                 label=f, alpha=0.6)
    plt.title(f'Comparaison du nombre d\'affectations entre les algorithmes [{t}]')
    plt.ylabel('Nombre d\'affectations')
    plt.xlabel('Taille de l\'entrée [nombre d\'éléments]')
    plt.yscale('log')
    plt.xscale('log')
    plt.grid(True)
    plt.legend()
    plt.savefig(f'compare_ops_swp_{t}.svg')
    cnt += 1

cnt = 1
print(ops_data['stable_sort'])
print(ops_data['sort'])
for t in ['ascendant', 'descendant', 'non-ordonné', 'partiellement ordonné']:
    plt.figure(figsize=(12, 6))
    for f in files:
        plt.plot([int(i) if int(i) != 0 else 1 for i in ops_data[f]['cmp'][0]], [int(i) if int(i) != 0 else 1 for i in ops_data[f]['cmp'][cnt]], marker='o',
                 label=f, alpha=0.6)
    plt.title(f'Comparaison du nombre de comparaisons entre les algorithmes [{t}]')
    plt.ylabel('Nombre de comparaisons')
    plt.xlabel('Taille de l\'entrée [nombre d\'éléments]')
    plt.yscale('log')
    plt.xscale('log')
    plt.grid(True)
    plt.legend()
    plt.savefig(f'compare_ops_cmp_{t}.svg')
    cnt += 1

cnt = 1
for t in ['ascendant', 'descendant', 'non-ordonné', 'partiellement ordonné']:
    plt.figure(figsize=(12, 6))
    for k, v in dict_data.items():
        plt.plot([int(i) if int(i) != 0 else 1 for i in v[0]], [float(i) if float(i) != 0 else 1 for i in v[cnt]], marker='o', label=k)
    plt.title(f'Comparaison du temps d\'exécution des algorithmes de tri sur une même séquence [{t}]')
    plt.ylabel('Temps [ms]')
    plt.xlabel('Taille de l\'entrée [nombre d\'éléments]')
    plt.yscale('log')
    plt.xscale('log')
    plt.grid(True)
    plt.legend()
    plt.savefig(f'compare_{t}.svg')
    cnt += 1
