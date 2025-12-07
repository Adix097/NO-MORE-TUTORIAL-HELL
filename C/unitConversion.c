#include <stdio.h>
#include <string.h>

double distanceConvertor(double initialDistance, char giveUnit[], char conversionUnit[]);
double temperatureConvertor(double initialTemperature, char givenUnit, char conversionUnit);
double currencyConvertor(double initialCurrency, char givenUnit[], char conversionUnit[]);

int main() {
    char convertor[256];
    
    printf("Enter the type of conversion you want(temperature/currency/distance): ");
    scanf("%s", convertor);

    if ((strcmp(convertor, "distance") != 0) && 
        (strcmp(convertor, "temperature") != 0) && 
        (strcmp(convertor, "currency") != 0)) {
            printf("Enter a valid type of conversion!!");
            return 1;
    } else {
        if (strcmp(convertor, "distance") == 0) {
            double initialDistance;
            char givenUnit[4];
            char conversionUnit[4];
    
            printf("Enter the initial distance: ");
            scanf("%f", &initialDistance);
    
            printf("Enter the original unit: ");
            scanf("%s", &givenUnit);
    
            printf("Enter the unit you want to convert to: ");
            scanf("%s", &conversionUnit);
    
            int finalDistance = distanceConvertor(initialDistance, givenUnit, conversionUnit);
            printf("%6.2f", finalDistance);
        }
        
        if (strcmp(convertor, "temperature") == 0) {
            double initialTemperature;
            char givenUnit;
            char conversionUnit;
    
            printf("Enter the initial temperature: ");
            scanf("%f", &initialTemperature);
    
            printf("Enter the original unit: ");
            scanf("%c", &givenUnit);
    
            printf("Enter the unit you want to convert to: ");
            scanf("%c", &conversionUnit);
    
            int finalTemperature = temperatureConvertor(initialTemperature, givenUnit, conversionUnit);
            printf("%6.2f", finalTemperature);
        }
    
        if (strcmp(convertor, "currency") == 0) {
            double initialCurrency;
            char givenUnit[4];
            char conversionUnit[4];
            
            printf("Enter the initial currency: ");
            scanf("%f", &initialCurrency);
            
            printf("Enter the original unit: ");
            scanf("%s", &givenUnit);
    
            printf("Enter the unit you want to convert to: ");
            scanf("%s", &conversionUnit);
            
            int finalCurrency = distanceConvertor(initialCurrency, givenUnit, conversionUnit);
            printf("%6.2f", finalCurrency);
        }
    
        return 0;
    }

}

double distanceConvertor(double initialDistance, char givenUnit[], char conversionUnit[]) {
    if ((strcmp(givenUnit, "km") == 0) && (strcmp(conversionUnit, "m") == 0)) {
        return initialDistance * 1000;
    }
    if ((strcmp(givenUnit, "m") == 0) && (strcmp(conversionUnit, "km") == 0)) {
        return initialDistance / 1000;
    }
    if ((strcmp(givenUnit, "m") == 0) && (strcmp(conversionUnit, "cm") == 0)) {
        return initialDistance * 100;
    }
    if ((strcmp(givenUnit, "cm") == 0) && (strcmp(conversionUnit, "m") == 0)) {
        return initialDistance / 100;
    }
    if ((strcmp(givenUnit, "km") == 0) && (strcmp(conversionUnit, "cm") == 0)) {
        return initialDistance * 100000;
    }
    if ((strcmp(givenUnit, "cm") == 0) && (strcmp(conversionUnit, "km") == 0)) {
        return initialDistance / 100000;
    }
}

double temperatureConvertor(double initialTemperature, char givenUnit, char conversionUnit) {
    if (givenUnit == 'C' && conversionUnit == 'F') {
        return (initialTemperature * (9/5)) + 32;
    }
    if (givenUnit == 'F' && conversionUnit == 'C') {
        return (initialTemperature - 32) * (5/9);
    }
    if (givenUnit == 'F' && conversionUnit == 'K') {
        return ((initialTemperature - 32) * (5/9)) + 273.15;
    }
    if (givenUnit == 'K' && conversionUnit == 'F') {
        return ((9/5) * (initialTemperature - 273.15)) + 32;
    }
    if (givenUnit == 'C' && conversionUnit == 'K') {
        return initialTemperature + 273.15;
    }
    if (givenUnit == 'K' && conversionUnit == 'C') {
        return initialTemperature - 273.15;
    }
}

double currencyConvertor(double initialCurrency, char givenUnit[], char conversionUnit[]) {
    if ((strcmp(givenUnit, "INR") == 0) && (strcmp(conversionUnit, "USD") == 0)) {
        return initialCurrency * 0.011;
    }
    if ((strcmp(givenUnit, "USD") == 0) && (strcmp(conversionUnit, "INR") == 0)) {
        return initialCurrency * 89.89;
    }
    if ((strcmp(givenUnit, "USD") == 0) && (strcmp(conversionUnit, "YEN") == 0)) {
        return initialCurrency * 155.18;
    }
    if ((strcmp(givenUnit, "YEN") == 0) && (strcmp(conversionUnit, "USD") == 0)) {
        return initialCurrency * 0.0064;
    }
    if ((strcmp(givenUnit, "INR") == 0) && (strcmp(conversionUnit, "YEN") == 0)) {
        return initialCurrency * 1.73;
    }
    if ((strcmp(givenUnit, "YEN") == 0) && (strcmp(conversionUnit, "INR") == 0)) {
        return initialCurrency * 0.58;
    }
}


