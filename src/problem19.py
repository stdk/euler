from calendar import monthrange
from collections import Counter


def simple():
    result = []
    for year in xrange(1901, 2001):
        result.append(0)
        for month in xrange(1, 13):
            day_of_week, days_in_month = monthrange(year, month)
            if day_of_week == 6:
                result[-1] += 1
    return result



non_leap = Counter((monthrange(1900, i)[0] + 1) % 7 for i in range(1, 13))
leap = Counter((monthrange(1900, i)[0] + 1 + (1 if i > 2 else 0)) % 7 for i in range(1, 13))

print non_leap
print leap

print simple()
print sum(simple())


def index_generator(value):
    while True:
        yield non_leap[(7 - (value + 1)) % 7]
        yield non_leap[(7 - (value + 2)) % 7]
        yield non_leap[(7 - (value + 3)) % 7]
        yield leap[(7 - (value + 4)) % 7]
        value += 5


print [i[0] for i in zip(index_generator(0), xrange(100))]

print sum(i[0] for i in zip(index_generator(0), xrange(100)))



