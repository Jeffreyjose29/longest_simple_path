# Поиск самого длинного пути в графе
## Потехин Сергей, 156 группа

1. Алгоритм градиентного спуска
2. Алгоритм Метрополиса с отжигом
3. Алгоритм Метрополиса без отжига

## Описание проекта
- [Algorithms.cpp](https://github.com/pavlovdog/longest_simple_path/blob/master/Algorithms.cpp) - реализация всех трех алгоритмов на C++
- [Algorithms.ipynb](https://github.com/pavlovdog/longest_simple_path/blob/master/Algorithms.ipynb) - реализация алгоритмов на Python 2.7, генерация & использование случайных графов, отрисовка графов и путей. Изначально весь код писался на Python, а потом портировался на C++, поэтому данный файл лучше написан, закомментирован и т.д.
- [env.py](https://github.com/pavlovdog/longest_simple_path/blob/master/env.py) - реализация функций энергии, поиска нового состояния и т.д.
- [graph_pictures](https://github.com/pavlovdog/longest_simple_path/tree/master/graph_pictures) - примеры найденных путей для разных графов
- [table_result.csv](https://github.com/pavlovdog/longest_simple_path/blob/master/table_result.csv) - сравнение результатов работы различных алгоритмах на различных графах (изменялось число вершин и вероятность ребер)

## Отчет
Вот пример работы алгоритмов для случайного графа на 19 вершинах с вероятностью появления ребра 0.2

### Случайный путь
![random](https://github.com/pavlovdog/longest_simple_path/raw/master/graph_pictures/1476217730.17_RANDOM_PATH.png "Random path")

### Путь, найденный градиентным спуском
![grad](https://github.com/pavlovdog/longest_simple_path/blob/master/graph_pictures/1476217730.17_GRADIENT_DESCENT.png "Grad path")

### Путь, найденный алгоритмом Метрополиса с отжигом
![metroanneal](https://github.com/pavlovdog/longest_simple_path/blob/master/graph_pictures/1476217730.17_METROPOLIS_WITH_ANNEALING.png "Metroanneal path")

### Путь, найденный алгоритмом Метрополиса без Отжига
![metro](https://github.com/pavlovdog/longest_simple_path/blob/master/graph_pictures/1476217730.17_METROPOLIS_WITHOUT_ANNEALING.png "Metro path")

По таблице, представленно
