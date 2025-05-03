import pandas
import numpy as np
import math

data = [
    [200, 4, 1, 0],
    [125, 7, 1, 0],
    [87, 1, 0, 0],
    [23, 9, 1, 1],
    [348, 3, 0, 1],
    [85, 7, 0, 1],
    [75, 2, 0, 1],
    [5, 8, 1, 1],
    [127, 1, 0, 0],
    [210, 3, 1, 0],
    [100, 6, 1, 1],
    [57, 5, 0, 1]
]

df = pandas.DataFrame(data, columns=['A1', 'A2', 'A3', 'Classe'])

def entropia(y):
    classes, counts = np.unique(y, return_counts=True)
    probs = counts / counts.sum()
    return -sum(p * math.log2(p) for p in probs if p > 0)

# dividir usando mediana
def dividir(df, features):
    base_entropy = entropia(df['Classe'])
    best_ig = -1
    best_attr = None
    best_value = None

    for attr in features:
        if attr in ['A1', 'A2']:
            threshold = df[attr].median()
            left = df[df[attr] <= threshold]
            right = df[df[attr] > threshold]
        else:  # Atributo 3 é só 0 ou 1
            threshold = 0
            left = df[df[attr] == 0]
            right = df[df[attr] == 1]

        if len(left) == 0 or len(right) == 0:
            continue

        e_left = entropia(left['Classe'])
        e_right = entropia(right['Classe'])
        e_total = (len(left) / len(df)) * e_left + (len(right) / len(df)) * e_right
        ig = base_entropy - e_total

        if ig > best_ig:
            best_ig = ig
            best_attr = attr
            best_value = threshold

    return best_attr, best_value, best_ig

def id3(df, features, depth=0):
    classes = df['Classe'].unique()
    indent = "  " * depth

    if len(classes) == 1:
        print(f"{indent}→ Classe {classes[0]}")
        return

    if not features:
        majority_class = df['Classe'].mode()[0]
        print(f"{indent}→ Classe {majority_class} (majoritária)")
        return

    attr, value, ig = dividir(df, features)

    if attr is None:
        majority_class = df['Classe'].mode()[0]
        print(f"{indent}→ Classe {majority_class} (sem ganho)")
        return

    if attr in ['A1', 'A2']:
        print(f"{indent}[{attr} ≤ {value:.2f}]")
        left = df[df[attr] <= value]
        right = df[df[attr] > value]
    else:
        print(f"{indent}[{attr} = 0]")
        left = df[df[attr] == 0]
        right = df[df[attr] == 1]

    id3(left, features, depth + 1)

    if attr in ['A1', 'A2']:
        print(f"{indent}[{attr} > {value:.2f}]")
    else:
        print(f"{indent}[{attr} = 1]")
    id3(right, features, depth + 1)

features = ['A1', 'A2', 'A3']
id3(df, features)