#include "graph.hpp"

// cities
enum City {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    L,
    M,
    N,
    O,
    P,
    R,
    S,
    T,
    U,
    V,
    Z
};

int main() {
    // create graph
    Graph graph(20);

    // add edge
    graph.addEdge(A, S, 140);
    graph.addEdge(A, T, 118);
    graph.addEdge(A, Z, 75);
    graph.addEdge(B, F, 211);
    graph.addEdge(B, G, 90);
    graph.addEdge(B, P, 101);
    graph.addEdge(B, U, 85);
    graph.addEdge(C, D, 120);
    graph.addEdge(C, P, 138);
    graph.addEdge(C, R, 146);
    graph.addEdge(D, M, 75);
    graph.addEdge(E, H, 86);
    graph.addEdge(F, S, 99);
    graph.addEdge(H, U, 98);
    graph.addEdge(I, N, 87);
    graph.addEdge(I, V, 92);
    graph.addEdge(L, M, 70);
    graph.addEdge(L, T, 111);
    graph.addEdge(O, S, 151);
    graph.addEdge(O, Z, 71);
    graph.addEdge(P, R, 97);
    graph.addEdge(R, S, 80);
    graph.addEdge(S, O, 151);
    graph.addEdge(U, V, 142);

    // add straight distance
    graph.addStraight(A, B, 366);
    graph.addStraight(B, B, 0);
    graph.addStraight(C, B, 160);
    graph.addStraight(D, B, 242);
    graph.addStraight(E, B, 161);
    graph.addStraight(F, B, 178);
    graph.addStraight(G, B, 77);
    graph.addStraight(H, B, 151);
    graph.addStraight(I, B, 226);
    graph.addStraight(L, B, 244);
    graph.addStraight(M, B, 241);
    graph.addStraight(N, B, 234);
    graph.addStraight(O, B, 380);
    graph.addStraight(P, B, 98);
    graph.addStraight(R, B, 193);
    graph.addStraight(S, B, 253);
    graph.addStraight(T, B, 329);
    graph.addStraight(U, B, 80);
    graph.addStraight(V, B, 199);
    graph.addStraight(Z, B, 374);

    // find shortest path from A to B
    graph.findShortestPath(A, B);
}