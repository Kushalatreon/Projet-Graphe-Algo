#include "../Headers/GrapheOriente.h"

GrapheOriente::GrapheOriente() : Graphe()
{}

GrapheOriente::GrapheOriente(std::vector<std::vector<int>> adj) : Graphe(adj)
{}

GrapheOriente::GrapheOriente(int nbSommets) : Graphe(nbSommets)
{
    initAdj();
}

int GrapheOriente::sommet_accessible(int sommet, const std::vector<int> &num) const
{
    int n = 0;
    for(int i = 1; i <= d_adj[0][0]; i++)
    {
        if(d_adj[sommet][i] > 0 && num[i] == 0)
        {
            n++;
        }
    }
    return n;
}

void GrapheOriente::numerotation(std::vector<int> &num, std::vector<int> &cfc, std::vector<int> &prem, std::vector<int> &pilch, int sommet, int &nNum, int &numCfc) const
{
    if(sommet_accessible(sommet, num) == 0)
    {
        num[sommet] = nNum++;
        cfc[sommet] = numCfc;
        prem[numCfc++] = sommet;
    }
    else
    {
        for(int i = 1; i <= d_adj[0][0]; i++)
        {
            if(d_adj[sommet][i] > 0 && num[i] == 0)
            {
                num[sommet] = nNum++;
                cfc[sommet] = numCfc;
                pilch[sommet] = i;
                numerotation(num, cfc, prem, pilch, i, nNum, numCfc)

            }

        }

    }
}

int GrapheOriente::frondeMin(int s, const std::vector<int> &num) const
{
    int vmin = INT32_MAX;
    for(int i = 1; i <= d_adj[0][0]; i++)
    {
        if(d_adj[s][i] > 0)
        {
            vmin = std::min(vmin, num[i]);
        }
    }
    return vmin;
}

void GrapheOriente::det_ro(const std::vector<int> &prem, const std::vector<int> &pilch, const std::vector<int> &num, std::vector<int> &ro) const
{
    for(int i = 1; i <= d_adj[0][0]; i++)
    {
        int s = prem[i];

        while(pilch[s] != 0)
        {
            int vro;
            if(s == prem[i])
            {
                vro = INT32_MAX;
            }
            else
            {
                vro = ro[num[s]+1];
            }

            ro[s] = std::min( num[s], std::min( vro, frondeMin(s, num)));

            s = pilch[s];
        }

    }
}

void GrapheOriente::tarjan(std::vector<int> &num, std::vector<int> &prem, std::vector<int> &pilch, std::vector<int> &ro, std::vector<int> &cfc, int sommet) const
{
    int nNum = 1, numCfc = 1;
    numerotation(num, cfc, prem, pilch, sommet, nNum, numCfc);

    for(int i = 1; i <= d_adj[0][0]; i++)
    {
        if(num[i] == 0)
        {
            numerotation(num, cfc, prem, pilch, i, nNum, numCfc);
        }
    }

    det_ro(prem, pilch, num, ro);
}

void GrapheOriente::ordonnancement(std::vector<int> fp, std::vector<int> app, std::vector<int> d, std::vector<int> &lc, std::vector<int> &fpc, std::vector<int> &appc) const
{
    int n = app[0], kc = 1, t;
    lc.resize(n+1);
    lc[0] = n;
    fpc.resize(fp[0] + 1);
    appc.resize(n + 1);
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

void GrapheOriente::graphe_reduit(std::vector<int> fs, std::vector<int> aps, std::vector<int> prem, std::vector<int> pilch, std::vector<int> cfc, std::vector<int> &fsr, std::vector<int> &apsr)
{
    int n = aps[0], nbc = prem[0], kr = 1, s, t;
    fsr.resize(fs[0] + 1);
    apsr.resize(nbc + 1);
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

void GrapheOriente::det_cfc(std::vector<std::vector<int>>dist, std::vector<int> &prem, std::vector<int> &pilch, std::vector<int> &cfc)
{
    int nb = 0, l;
    int n = dist[0][0];
    prem.resize(n + 1);
    pilch.resize(n + 1);
    cfc.resize(n + 1);
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




/* int*& prem et int*& num sont optionnel
 * std::vector<int> &prem doit avoir son maximum à n-1 avant l'appel à la fonction
 * int& r, le maximum des rangs finis trouvé*/
bool GrapheOriente::m_rangs(std::vector<int>fs, std::vector<int>aps, int& r, std::vector<int>&m_rangs/*int*& prem, int*& num*/) const
{


    std::vector<int>ddi;
    int n = aps[0];
    m_rangs.resize(n+1);
    det_ddi(fs, aps, ddi);
    int s;
    int k = 0;
    //int p = 1; //Si on utilise int*& num
    std::vector<int>pilch;
    //num.resize()(ddi[0]+1];
    pilch.resize(ddi[0]+1);
    pilch[0] = 0;
    for(int i = 1; i <= ddi[0]; i++)
    {
        m_rangs[i] = -1;
        if(ddi[i] == 0)
        {
            pilch[i] = pilch[0];
            pilch[0] = i;
        }
    }
    while(pilch[0] > 0)
    {
        s = pilch[0];
        //prem[r] = s; //Si on utilise int*& prem
        pilch[0] = 0;
        while(s > 0)
        {
            m_rangs[s] = r;
            //num[s] = p++; //Si l'on utilise int*& num
            k++;
            for(int h = aps[s]; (fs[h]) != 0; h++)
            {
                int t = fs[h];
                ddi[t]--;
                if(ddi[t] == 0)
                {
                    pilch[s] = pilch[0];
                    pilch[0] = s;
                }
                s = pilch[s];
            }
            r++;
        }
        r--;
        return(k == n);
    }

}

void GrapheOriente::adj_2_fs_aps(std::vector<int> &fs, std::vector<int> &aps) const
{
    int n = d_adj[0][0], m = d_adj[0][1];
    /*int m = 0;
     *for (int i = 1; i <= d_adj[0][0]; i++) //Si l'on utilise la première ligne/colonne
     *  if(d_adj[i][0] > 0)
     *      m += d_adj[i][0]; */
    fs.resize(n + m + 1);
    fs[0] = n + m;

    aps.resize(n + 1);
    aps[0] = n;

    int k =1;
    for(int i = 1 ; i <= n ; i++)
    {
        aps[i] = k;
        for(int j = 1 ; j <= n ; j++)
        {
            if(d_adj[i][j] >= 1)
                fs[k++] = j;
        }
        fs[k++] = 0;
    }
}
