# -*- coding: utf-8 -*-
from itertools import *
import time
def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s,r) for r in range(len(s)+1))
def main():
    n = 7
    vertices = range(1,n+1)
    _print_subgraphs = False
    edges = list(combinations(vertices,2))
    print "For the complete graph of",n,"vertices there are", len(edges),"edges."
    # for e in edges:
    #     print e
    start = time.time()
    _edges_powerset = list(powerset(list(edges)))
    end = time.time()

    no_subgraphs = len(_edges_powerset)
    print "There are",no_subgraphs,"possible subraphs."
    print "It took",(end-start),"seconds to compute the powerset of the edges with n=",n
    if _print_subgraphs:
        for s in _edges_powerset:
            print s


main()
