makedq (L, R, L', R') = if length L > c * length R + 1 then
                      let n = (length L + length R) / 2
                          L' = take(n, L)
                          R' = rot1(n, R, L)
                      in (L', R', L', R')
                   else if length R > c * length L + 1 then
                          let n = (length L + length R) / 2
                              L' = rot1(n, L, R)
                              R' = take(n, R)
                          in (L', R', L', R')
                        else (L, R, L', R')

insertL e (L, R, L', R') = makedq (e : L, R, tail L', tail R')

insertR e (L, R, L', R') = makedq (L, e : R, tail L', tail R')

removeL (L, R, L', R') =
  if length L == 0 then 
		(head R, [])
  else 
		if length L > 0 then 
			(head L, makedq (tail L, R, tail (tail L'), tail (tail R')))

removeR (L, R, L', R') =
  if length R == 0 then 
		(head L, [])
  else 
		if length R > 0 then
			(head R, makedq (L, tail R, tail (tail L'), tail (tail R')))

rot1 (n, L, R) = 
  if n >= c then head L : rot1(n - c, tail L, drop(c, R))
  else if n < c then rot2(L, drop(n, R), [])

rot2 (L, R, A) = 
  if length L < 0 && length R >= c then head L : rot2(tail L, drop(c, R), rev(take(c, R)) ++ A)
  else if length L == 0 || length R < c then L ++ rev R ++ A
---- Assumptions: tail [] = [].
