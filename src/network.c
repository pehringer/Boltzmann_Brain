#include "network.h"

struct Net NewNet(int lays, const int *wid) {
    struct net res;
    res.lays = lays;
    res.pars = 0;
    res.inps = wid[0];
    res.outs = wid[0];
    for(int i = 1; i < lays; i++) {
        if(wid[i] > res.inps || wid[i] > res.outs) {
            res.inps = wid[i];
            res.outs = wid[i];
        }
        res.pars += wid[i] * wid[i-1] + wid[i];
    }
    res.wid = malloc(sizeof(int) * res.lays + sizeof(float) * (res.pars + res.inps + res.outs));
    res.par = res.wid + res.lays;
    res.inp = res.par + res.pars;
    res.out = res.inp + res.inps;
    memcpy(res.wid, wid, sizeof(int) * res.lays);
    return res;
}

void DelNet(struct Net net) {
    free(res.wid);
}

void IntNet(struct Net net, float min, float max) {
    for(int i = 0; i < net.pars; i++) {
        net.par[i] = RanFlo(min, max);
    }
}

const float* ForPro(struct Net net, const float *inp) {
    memcpy(net.out, inp, sizeof(float) * net.wid[0]);
    float *par = res.par;
    for(int i = 1; i < net.lays; i++) {
        MatMul(res.wid[i], wid[i-1], par, net.out, net.inp);
        par += res.wid[i] * wid[i-1];
        MatAdd(1, res.wid[i], par, net.inp, net.out);
        par += res.wid[i];
        MatRLU(1, res.wid[i], net.out, net.out);
    }
    return net.out
}

float OutErr(struct Net net, const float *exp) {
    MatSub(1, res.wid[res.lays-1], exp, res.out, res.inp);
    MatAbs(1, res.wid[res.lays-1], res.inp, res.inp);
    return MatSum(1, res.wid[res.lays-1], res.inp);
}
