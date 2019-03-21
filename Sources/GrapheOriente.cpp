#include "../Headers/GrapheOriente.h"

GrapheOriente::GrapheOriente() : Graphe()
{}

GrapheOriente::GrapheOriente(int** adj) : Graphe(adj)
{}

GrapheOriente::GrapheOriente(int nbSommets) : Graphe(nbSommets)
{
    initAdj();
}

void GrapheOriente::ajouterArete(int predecesseur, int successeur)
{
    ajouterLisaison(predecesseur,successeur, 1);
}

void GrapheOriente::tarjan() const {

}

void GrapheOriente::ordonnancement(int *fp, int *app, int *d, int *&lc, int *&fpc, int *&appc) const
{
    int n = app[0], kc = 1, t;
    lc = new int [n+1];
    lc[0] = n;
    fpc = new int [fp[0] + 1];
    appc = new int [n + 1];
    appc[0] = n;
    lc[1] = 0;
    fpc[0] = 0;
    appc[1] = 4;
    for (int s = 2; s <= n; s++)
    {
        lc[s] = 0;
        appc[s] = kc + 1;
        for ( int k = app[s]; (t = fp[k]) != 0; k++)
        {
            int r = lc[t] +  d[t];
            if ( r >= lc[s])
            {
                if ( r > lc[s])
                {
                    kc = appc[s];
                    fpc[kc] = t;
                }
                else
                {
                    kc++;
                    fpc[kc] = t;
                }
            }

        }
        kc++;
        fpc[kc] = 0;
    }
    fpc[0] = kc;
}

void GrapheOriente::graphe_reduit(int *fs, int *aps, int *prem, int *pilch, int *cfc, int *&fsr, int *&apsr)
{
    int n = aps[0], nbc = prem[0], kr = 1, s, t;
    fsr = new int [fs[0] + 1];
    apsr = new int [nbc + 1];
    apsr[0] = nbc;
    bool *deja_mis = new bool[nbc + 1];
    for (int c = 1; c <= nbc; c++)
    {
        apsr[c] = kr;
        for (int i = 0; i <= nbc ; i++)
            deja_mis[i] = false;
        deja_mis[c] = true;
        s = prem[c];
        while ( s != 0)
        {
            for (int k = aps[0]; (t = fs[k]) != 0; k++)
            {
                if ( !deja_mis[cfc[t]])
                {
                    fsr[kr] = cfc[t];
                    deja_mis[cfc[t]] = true;
                    kr++;
                }
            }
            s = pilch[s];
        }
        fsr[kr] = 0;
        kr++;
    }
    fsr[0] = kr -1;
    delete [] deja_mis;
}

void GrapheOriente::det_cfc(int **dist, int *&prem, int *&pilch, int *&cfc)
{
    int nb = 0, l;
    int n = dist[0][0];
    prem = new int [n + 1];
    pilch =  new int [n + 1];
    cfc = new int [n + 1];
    for (int i = 1; i <= n; i++) cfc[i] = 0;
    cfc[0] = n;
    for (int i = 1; i <= n; i++)
    {
        if (cfc[i] == 0)
        {
            nb++;
            prem[nb] = i;
            cfc[i] = nb;
            l = i;
            for (int j = i+1; j < n ; ++j)
            {
                if((dist[i][i] != -1) && (dist[j][i] != -1) && (cfc[j] != 0) )
                {
                    pilch[l] = j;
                    cfc[j] = nb;
                    l = j;
                }
            }
            pilch[l] = 0;
        }
    }
}

void GrapheOriente::det_ddi(const int* fs, const int* aps, int* &ddi) const
{
    int n = aps[0];
    ddi = new int[n + 1];

    for (int i = 0 ; i <= n ; ++i)
        ddi[i] = 0;

    for (int i = 1 ; i <= n ; ++i)
        ++ddi[fs[i]];
}

void GrapheOriente::det_app(int* ddi, int* &app) const
{
    int n = ddi[0];
    app = new int[n +1 ];
    app[0] = n;
    app[1] = 1;

    for (int i = 2 ; i <= n ; ++i)
        app[i] = app[i - 1] + ddi[i - 1] + 1;
}

void GrapheOriente::fs_aps_2_fp_app(int* fs, int* aps, int* &fp, int* &app) const
{
    int* ddi;
    int n = fs[0];
    int j;

    det_ddi(fs, aps, ddi);
    det_app(ddi, app);
    fp[0] = fs[0];

    for(int i = 1 ; i <= n ; ++i)
        for (int k = aps[i] ; (j = fs[k]) != 0 ; ++k)
            fp[app[j]++] = i;

    for (int i = 1 ; i <= n ; ++i)
        fp[app[i]] = 0;

    for (int i = n ; i > 1 ; --i)
        app[i] = app[i - 1] + 1;

    app[1] = 1;

    delete[] ddi;
}