from functools import cache

num_map = {c: (i % 3, i // 3) for i, c in enumerate('789456123 0A')}
dir_map = {c: (i % 3, i // 3) for i, c in enumerate(' ^A<v>')}

def gen_moves(s, t, f):
    h = '>' * (t[0] - s[0]) if s[0] < t[0] else '<' * (s[0] - t[0])
    v = 'v' * (t[1] - s[1]) if s[1] < t[1] else '^' * (s[1] - t[1])
    if s[1] == f[1] and t[0] == f[0]:
        return {v + h + 'A'}
    if s[0] == f[0] and t[1] == f[1]:
        return {h + v + 'A'}

    return {v + h + 'A', h + v + 'A'}

@cache
def best_expansion(cmd, level):
    if level == 0:
        return len(cmd), cmd

    exps = [[]]
    for p, c in zip('A' + cmd, cmd):
        new_exps = []
        for m in gen_moves(dir_map[p], dir_map[c], dir_map[' ']):
            new_exps.extend([*r, m] for r in exps)
        exps = new_exps

    return min((sum(best_expansion(cmd, level - 1)[0] for cmd in exp), exp) for exp in exps)

def main(rounds):
    result = 0
    for cmd in open('input.txt').read().splitlines():
        result += int(cmd[0:3]) * sum(
            min(best_expansion(cmd, rounds)[0] for cmd in gen_moves(num_map[p], num_map[c], num_map[' ']))
            for p, c in zip('A' + cmd, cmd))

    print(result)

main(2)
main(25)
