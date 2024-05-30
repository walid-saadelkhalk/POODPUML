#include "../hpp_files/Tower.hpp"

Tower::Tower(int x, int y, float attackPower, float lifeBar, int evolveStatus, double damage, bool selected, int shotRate)
    : Entities(x, y), attackPower(attackPower), lifeBar(lifeBar), evolveStatus(evolveStatus), damage(damage), selected(selected), shotRate(shotRate) {
}

void Tower::upgrade() {
    // Implémentez la logique pour améliorer la tour ici
}

void Tower::someVirtualMethod() {
    // Implémentez la méthode virtuelle ici
}
