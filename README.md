Semestrální práce z C++

Zadání: Výpočet determinantu matice

Implementace:
Determinant je počítán pomocí Gaussovy eliminace. Matice je převedena do horního trojúhelníkového tvaru a následně je její diagonála vynásobena 
(samozřejmě s ohledem na znaménko determinantu, které mohlo být změněno při určitých operacích během převodu do trojúhelníkového tvaru)

Program může počítat determinant pro matice zadané uživatelem na standardní vstup,
nebo zadaný počet náhodně vygenerovaných matic o zadané velikosti, s nebo bez využití implementované paralelizace.
(detaily jsou dostupné v přepínači '--help')

Paralelizace spočívá ve výpočtu více determinantů najednou, měření času probíhá při každém výpočtu a je vypsáno na výstup.
