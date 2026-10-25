# Taller2_PrissylaGomez
Nombre: Prissyla Gomez Diaz
Rut: 21.818.649-1
Nombre en Github: Prissyla Gomez
Carrera: Inngenieria en computacion e informatica

Intrucciones de compilacion: g++ main.cpp cola.h cola.cpp stack.h stack.cpp nodoPaciente.h paciente.h paciente.cpp nodoAVL.h arbolAVL.h arbolAVL.cpp rutaDecision.h rutaDecision.cpp nodoServicio.h servicios.h servicios.cpp hospital.h hospital.cpp -o j
Intrucciones de ejecucion: .\j

Criterios del arbol de decision: Me base en el ejemplo que venia en las instrucciones del taller, pero le agrege algunas cosas para que fuera mas completo. Agrege que si la presion es igual o superor a 140 tambien va a Cardiología, ademas con fiebre mayor o igual a 39°C y dolor mayor o igual a 8 se deriva a Urgencias. 
Justificacion paso a paso: si Edad <14 -> Pediatria, si trauma = 1 -> se evalua si requiere cirugia = 1 -> Cirugia, si no -> traumatologia, si sintomas neurologicos = 1 -> neurologia, si tipoDolor = pecho o presionArterial >= 140 -> cardiologia, si temperatura >= 39°C o dolor >= 8 -> Urgencias, si diasHospitalizacion >= 2 -> Hospitalizacion, si no cumple con ninguno de los criterios -> medicinaGeneral.