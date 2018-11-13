#include "mouvement_sse.h"

uint8** sigma_delta_sse (uint8 **I, uint8 **M_1, uint8 **V_1, long nrl, long nrh, long ncl, long nch)
{
    uint8** E = ui8matrix(nrl, nrh, ncl, nch);

    for(long i=nrl; i<nrh; i++)
    {
        for(long j=nrh; j<nch; j+=16)
        {
            vuint8 ones = _mm_set1_epi8(1);
            vuint8 tmp = _mm_set1_epi8(-128);

            vuint8 vI = _mm_load_si128((vuint8*) &I[i][j]);
            //display_vuint8(vI, " %3d", "  vI"); puts("");

            vuint8 vM_1 = _mm_load_si128((vuint8*) &M_1[i][j]);
            //display_vuint8(vM_1, " %3d", "vM_1"); puts("");

            vuint8 vV_1 = _mm_load_si128((vuint8*) &V_1[i][j]);
            //display_vuint8(vV_1, " %3d", "vV_1"); puts("");

            // Étape 1
            vM_1 = _mm_add_epi8(vM_1, tmp); // Conversion u->s
            vI = _mm_add_epi8(vI, tmp); // Conversion u->s
            vuint8 vLT = _mm_and_si128(ones, _mm_cmplt_epi8(vM_1, vI)); // Garder le LSB
            vuint8 vGT = _mm_and_si128(ones, _mm_cmpgt_epi8(vM_1, vI)); // Garder le LSB
            vuint8 vM = _mm_add_epi8(vM_1, vLT);
            vM = _mm_sub_epi8(vM, vGT);
            vM = _mm_add_epi8(vM, tmp); // Conversion s->u
            //display_vuint8(vM, " %3d", "  vM"); puts("");

            // Étape 2
            vM = _mm_add_epi8(vM, tmp); // Conversion u->s
            vuint8 vO = _mm_abs_epi8(_mm_sub_epi8(vM, vI));
            //display_vuint8(vO, " %3d", "  vO"); puts("");

            // Étape 3
            vuint8 t =_mm_load_si128(&vO);
            uint8 *p = (uint8*) &t;
            for(uint8 i=0; i<16; i++)
                p[i] *= N;
            //display_vuint8(t, " %3d", "  vT"); puts("");

            vV_1 = _mm_add_epi8(vV_1, tmp); // Conversion u->s
            vLT = _mm_and_si128(ones, _mm_cmplt_epi8(vV_1, t)); // Garder le LSB
            vGT = _mm_and_si128(ones, _mm_cmpgt_epi8(vV_1, t));
            vuint8 vV = _mm_add_epi8(vV_1, vLT);
            vV = _mm_sub_epi8(vV, vGT);
            vV = _mm_add_epi8(vV, tmp); // Conversion s->u
            vV = _mm_max_epu8(_mm_min_epu8(vV, _mm_set1_epi8(VMAX)), _mm_set1_epi8(VMIN));

            // Étape 4
            //display_vuint8(vV, " %3d", "  vV"); puts("");
            vO = _mm_add_epi8(vO, tmp);
            vV = _mm_add_epi8(vV, tmp);
            vuint8 vE = _mm_subs_epu8(_mm_set1_epi8(0xff), _mm_cmplt_epi8(vO, vV));
            //display_vuint8(vE, " %3d", "  vE"); puts("");

            vM = _mm_add_epi8(vM, tmp); // Conversion s->u
            vV = _mm_add_epi8(vV, tmp); // Conversion s->u
            _mm_store_si128((vuint8*) &M_1[i][j], vM);
            _mm_store_si128((vuint8*) &V_1[i][j], vV);
            _mm_store_si128((vuint8*) &E[i][j], vE);
        }
    }

    return E;
}