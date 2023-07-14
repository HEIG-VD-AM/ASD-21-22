import pandas as pd
from io import StringIO

files = ['quicksort.csv', 'radix1.csv', 'radix2.csv', 'radix4.csv', 'radix8.csv', 'radix16.csv']
path = '../../src/cmake-build-debug/'

# Traitement des fichiers CSV sortis par le logiciel
buffer = ""
for i, f in enumerate(files):
    with open(path + f) as csvfile:
        lines = csvfile.readlines()
        if i == 0:
            # On envoie dans le buffer la première ligne du fichier
            buffer = lines[0]
        buffer += f"mesure de {f[:-4]}," + lines[1][7:]

# sauvegarde des résultats
with open('../csv/results.csv', 'w') as csvfile:
    csvfile.write(buffer)
    csvfile.close()

# Génération du plot
columns = {"mesure de quicksort": 'quicksort',
           "mesure de radix1": 'radix1',
           "mesure de radix2": 'radix2',
           "mesure de radix4": 'radix4',
           "mesure de radix8": 'radix8',
           "mesure de radix16": 'radix16'}

# Manipulation pour retirer le premier élément de la première ligne du csv (nombre d'entrée)
buffer = pd.read_csv(StringIO(buffer), sep=',', index_col=0).T.to_csv()
df = pd.read_csv(StringIO(buffer), sep=',', index_col=0)
df.rename(columns=columns, inplace=True)

ax = df.plot(figsize=(12, 6), loglog=True, fontsize=12)
ax.set_ylabel(r"Temps [$ms$]", fontsize=12)
ax.set_xlabel("Taille de l'échantillon", fontsize=12)
ax.set_title('Comparaison des algorithmes de tri', fontsize=12)
ax.get_figure().savefig('results.svg')
