#include <iostream>
#include "TSP.hpp"
#include "SA.hpp"
#include "Tabu.hpp"

int main(int argc, char const *argv[])
{
  std::cout << "PEA Project!" << std::endl;

    const double minTemp=0.0001;
    const unsigned int it=10;

    
    TSP tsp;
    uint8_t selected = -1;
    int stopCriteria = 20;
    string filename;
    double coolingFactor = 0.9999;
    
    int maxOrderNotChanged=1000;
    
    bool dataLoaded = false;
    
    while (selected != '0')
    {
        cout << '\a';
        cout << '\7';

        cout << "\n\nPEA Projekt - Tobiasz Puślecki 241354" << endl;
        cout << "1.Wczytanie danych z pliku" << endl;
        cout << "2.Wygenerowanie danych losowych" << endl;
        cout << "3.Wyświetlenie danych" << endl;
        cout << "4.Kryterium stopu" << endl;
        cout << "5.TS" << endl;
        cout << "6.Współczynnik zmiany temperatury" << endl;
        cout << "7.SA" << endl;
        cout << "0. Wyjście" << endl;
        cout << ">>> ";
        cin >> selected;
        
        if(selected == '1')
        {
            cout << "Podaj nazwę pliku: ";
            cin >> filename;
            
            TSP tsp_(filename);
            tsp = tsp_;
            dataLoaded = true;
            
        }
        else if (selected == '2')
        {
            cout << "Podaj rozmiar: ";
            string dim;
            cin >> dim;
            TSP tsp_(stoi(dim));
            tsp = tsp_;
            dataLoaded = true;
        }
        else if (selected == '3')
        {
            if(dataLoaded)
                tsp.printMatrix();
            else
                cout << "Nie wczytano/wylosowano danych!\n";
        }
        else if (selected == '4')
        {
            int stopCriteria_;
            cout << "Podaj kryterium stopu w sekundach (>0)\n";
            cin >> stopCriteria_;
            if (stopCriteria_ > 0 and stopCriteria_ < INT_MAX)
            {
                stopCriteria = stopCriteria_;
            }
            else
            {
                cout << "Niepoprawne dane ! \n";
            }
        }
        else if (selected == '5')
        {
            if(dataLoaded)
            {
                Tabu tabu(tsp.getMatrix());
                cout << fixed << endl;
                cout << "Tabu| path: " << tabu.calculate(stopCriteria,maxOrderNotChanged) << "  in time:  " << tabu.getExecutionTime() << "\n\n\n";
            }
            else
            {
                cout << "Nie wczytano/wylosowano danych!\n";
            }
        }
        else if (selected == '6')
        {
            double coolingFactor_;
            cout << "Podaj współczynnik zmiany temperatury (0;1)\n";
            cin >> coolingFactor_;
            if (coolingFactor_ > 0 and coolingFactor_ < 1.0)
            {
                coolingFactor = coolingFactor_;
            }
            else
            {
                cout << "Niepoprawne dane ! \n";
            }
        }
        else if (selected == '7')
        {
            if(dataLoaded)
            {
                SA sa(tsp.getMatrix());
                cout << fixed << endl;
                cout << "SA| path: " << sa.calculate(it,stopCriteria,minTemp,coolingFactor) << "  in time:  " << sa.getExecutionTime() << "\n\n\n";
            }
            else
            {
                cout << "Nie wczytano/wylosowano danych!\n";
            }
        }
    }
  return 0;
}
