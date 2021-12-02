parents(igor_glushatov, olga_bespalova, sergey_glushatov).
parents(olga_bespalova, margarita_fadeeva, sergey_bespalov).
parents(svetlana_bespalova, margarita_fadeeva, sergey_bespalov).
parents(sergey_glushatov, lidia_sidorova, anatoly_glushatov).
parents(yulya_glushatova, lidia_sidorova, anatoly_glushatov).
parents(vladimir_korolev, svetlana_bespalova, ilya_korolev).
parents(semen_korolev, svetlana_bespalova, ilya_korolev).
parents(margarita_fadeeva, maria_yerikova, michail_fadeyev).
parents(yuri_fadeyev, maria_yerikova, michail_fadeyev).
parents(valery, yulya_glushatova, alexander_lyubushkin).
parents(yakob, yulya_glushatova, alexander_lyubushkin).
parents(sergey_bespalov, seraphima_zakharova, nikolay_bespalov).
parents(maria_yerikova, pelageya, undefind3).
parents(valentina_erykova, pelageya, undefind3).
parents(tatyana_erykova, pelageya, undefind3).
parents(konstantin_erykov, pelageya, undefind3).
parents(nikolay_erykov, pelageya, undefind3).
parents(yuliya_fadeyev, galina_mironova, yuri_fadeyev).
parents(daniil_dozorets, yuliya_fadeyev, dmitriy_dozorets).
parents(artemiy_dozorets, yuliya_fadeyev, dmitriy_dozorets).
parents(seraphima_zakharova, undefind0, undefind4).
parents(valentina_zaharova, undefind0, undefind4).
parents(lidia_zaharova, undefind0, undefind4).
parents(lubov, valentina_zaharova, undefind1).
parents(ghalina_parandyk, lubov, undefind2).
parents(maya_parandyk, lubov, undefind2).
sex(pelageya, female).
sex(yuri_fadeyev, male).
sex(seraphima_zakharova, female).
sex(nikolay_bespalov, male).
sex(dmitriy_dozorets, male).
sex(yuliya_fadeyev, female).
sex(artemiy_dozorets, male).
sex(daniil_dozorets, male).
sex(vladimir_korolev, male).
sex(ilya_korolev, male).
sex(maya_parandyk, female).
sex(undefind2, male).
sex(konstantin_erykov, male).
sex(lubov, female).
sex(nikolay_erykov, male).
sex(igor_glushatov, male).
sex(olga_bespalova, female).
sex(sergey_glushatov, male).
sex(margarita_fadeeva, female).
sex(sergey_bespalov, male).
sex(anatoly_glushatov, male).
sex(svetlana_bespalova, female).
sex(lidia_zaharova, female).
sex(valentina_erykova, female).
sex(tatyana_erykova, female).
sex(galina_mironova, female).
sex(undefind0, female).
sex(valentina_zaharova, female).
sex(semen_korolev, male).
sex(maria_yerikova, female).
sex(alexander_lyubushkin, male).
sex(valery, male).
sex(michail_fadeyev, male).
sex(yulya_glushatova, female).
sex(michael_fadeev, male).
sex(yakob, male).
sex(lidia_sidorova, female).
sex(ghalina_parandyk, female).
sex(undefind1, male).

sibling(X, Y) :- parents(X, A, B), parents(Y, A, B), X\=Y.
brother(X, Y) :- sibling(X, Y), sex(Y, male).
sister(X, Y) :- sibling(X, Y), sex(Y, female).
cousin(X, Y) :- parents(X, A, B), sibling(A, AA), parents(Y, AA, Z). 
cousin(X, Y) :- parents(X, A, B), sibling(A, AA), parents(Y, Z, AA). 
cousin(X, Y) :- parents(X, A, B), sibling(B, BB), parents(Y, BB, Z). 
cousin(X, Y) :- parents(X, A, B), sibling(B, BB), parents(Y, Z, BB). 
husband(X, Y) :- parents(A, X, Y).
wife(X, Y) :- husband(Y, X).  
mother(X, Y) :- parents(X, Y, Z).
father(X, Y) :- parents(X, Z, Y).
teshya(X, Y) :- wife(X, Z), mother(Z, Y).

relative(sibling, X, Y) :- sibling(X, Y).