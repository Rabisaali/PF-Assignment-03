#include <stdio.h>
#define FIXED_GRAVITY 10.0
void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets);

int main () {

    int fuel, consumption, recharge, solarBonus, totalPlanets;
    printf("Enter total fuel: ");
    scanf("%d", &fuel);
    printf("Enter the consumption per each planet: ");
    scanf("%d", &consumption);
    printf("Enter the regeneration value of fuel: ");
    scanf("%d", &recharge);
    printf("Enter the solar bonus: ");
    scanf("%d", &solarBonus);
    printf("Enter total planets: ");
    scanf("%d",&totalPlanets);

    int planetNumber = 1;

    calculateFuel(fuel, consumption, recharge, solarBonus, planetNumber, totalPlanets);
    return 0;
}
void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    if (fuel<=0 || planet>totalPlanets) {
        if (fuel<=0) {
            printf("\nMission failed due to insufficient fuel. Reached planet %d\n", planet-1);
        } else {
            printf("\nMission successful. Fuel left after reaching planet %d: %d\n", planet, fuel);
        }
        return;
    }

    printf("Enter the value of gravity of planet number %d: ", planet);
    float gravity;
    scanf("%f", &gravity);
    if (gravity==FIXED_GRAVITY) fuel+=recharge;

    fuel -= consumption;

    if (planet%4==0) fuel+=solarBonus;

    if (fuel < 0) fuel = 0;

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);
    planet++;
    calculateFuel(fuel, consumption, recharge, solarBonus, planet, totalPlanets);
    return;
}