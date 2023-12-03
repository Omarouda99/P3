PAV - P3: detección de pitch
============================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 3](https://github.com/albino-pav/P3).
Siga las instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para realizar un `fork` de la
misma y distribuir copias locales (*clones*) del mismo a los distintos integrantes del grupo de prácticas.

Recuerde realizar el *pull request* al repositorio original una vez completada la práctica.

Ejercicios básicos
------------------

- Complete el código de los ficheros necesarios para realizar la detección de pitch usando el programa
  `get_pitch`.

   * Complete el cálculo de la autocorrelación e inserte a continuación el código correspondiente.
	```.sh
	for (unsigned int l = 0; l < r.size(); ++l) {
		r[l]=0;
		for (unsigned int n = 0; n < x.size(); ++n) {
			r[l] += x[n]*x[n+l];
		}
		r[l] = r[l]/x.size();
	}
 	```
   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.

	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la librería matplotlib de Python.

    ![image](https://user-images.githubusercontent.com/92537816/143685646-4dfd0eff-d162-4186-bd46-c6e5e79b2daf.png)
    
    Podem veure que el període de pitch és aproximadament 6ms, que és aprox. l'invers de la posició del màxim en l'autocorrelació.
        
    <img width="68" alt="2021-11-27" src="https://user-images.githubusercontent.com/92537816/143686131-6043852c-79db-4c3e-b2ba-85c9d35dfa29.png">
    
    ![image](https://user-images.githubusercontent.com/92537816/144066736-f531fddb-0398-49b2-951e-9a7ca0720c8f.png)

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.

	```.sh
	for(iR=iRMax=r.begin()+npitch_min; iR<r.begin()+npitch_max; iR++){
		if(*iR>*iRMax){
			iRMax=iR;
 		}
	}
 	```

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.
   
Utilitzant 3 valors: l'autocorrelació, la relació R(1)/R(0) i el valor de la potencia.
Com que les trames de sons sords tenen l'autocorrelació és molt diferent a la seva energia podem detectar-los fàcilment. També podem detectar trames de silenci ja que la seva energia és baixa i està per sota del threshold que hem
marcat.

 	if(rmaxnorm>umaxnorm && r1norm > r1thr && pot > powthr){
  		return false; //para sonoro
    	}
     	return true; //para sordo
    

- Una vez completados los puntos anteriores, dispondrá de una primera versión del detector de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la detección de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).
		
	Creant un .out, podem separar les columnes per extreure els nostres paràmetres amb la següent ordre:
	![Alt text](image-2.png)

	![image](https://user-images.githubusercontent.com/92537816/144089248-e9f07c9b-dd7b-47a5-9137-426781c9be8b.png)
	Podem veure (de dalt a baix): la forma d'ona, el nivell de potència de la senyal, r1norm i rmaxnorm.		

	![image](https://user-images.githubusercontent.com/92537816/144092111-8d295d17-768c-4571-b6a4-9f58c14b8e68.png)
	Aquí podem veure la nostra detecció de pitch a sobre (amb les millors prestacions aconseguides), i la que fa wavesurfer a sota.

      - Use el detector de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos detectores.
  
  * Optimice los parámetros de su sistema de detección de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..
	
	Amb paràmetres optimitzats i sense pre ni postprocessat, el nostre sistema de detecció de Pitch té una puntuació de 91.12%
	
	![image](https://github.com/Omarouda99/P3/assets/99822243/20b603c4-430b-41cb-9e0d-f4fdad3f4726)


   * Inserte una gráfica en la que se vea con claridad el resultado de su detector de pitch junto al del
     detector de Wavesurfer. Aunque puede usarse Wavesurfer para obtener la representación, se valorará
	 el uso de alternativas de mayor calidad (particularmente Python).
   	
	![image](https://user-images.githubusercontent.com/92537816/144068860-582dd19c-9bde-40c0-a47a-fec567f80941.png)

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  detector a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del detector. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la detección de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.
    
    ![image](https://github.com/Omarouda99/P3/assets/99822243/53d022f6-8172-4ca8-87d0-e90583e2b969)

   

- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de detección
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, *center clipping*, etc.
	Implementem center-clipping sense offset
 	```.sh
	float max = *std::max_element(x.begin(), x.end());
	for(int i = 0; i < (int)x.size(); i++) {
	    if(abs(x[i]) < cclip1*max) {
  	      x[i] = 0.0F;
	    } 
	}
 	```

  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.
    	Implementem el filtre de mitjana
 	```.sh
	vector<float> f0_final(f0.size());
	vector<float> temp(3);
	int i;
	for(i = 1; i < (int)(f0.size() - 1); i++) {
	    temp = {f0[i-1], f0[i], f0[i+1]};
	    auto m = temp.begin() + temp.size()/2;
	    std::nth_element(temp.begin(), m, temp.end());
	    f0_final[i] = temp[temp.size()/2];
	}
	f0_final[i] = f0_final[i-1];
	f0_final[0] = f0_final[1];

    
  * Optimización **demostrable** de los parámetros que gobiernan el detector, en concreto, de los que
    gobiernan la decisión sonoro/sordo.
  * Cualquier otra técnica que se le pueda ocurrir o encuentre en la literatura.

  Encontrará más información acerca de estas técnicas en las [Transparencias del Curso](https://atenea.upc.edu/pluginfile.php/2908770/mod_resource/content/3/2b_PS%20Techniques.pdf)
  y en [Spoken Language Processing](https://discovery.upc.edu/iii/encore/record/C__Rb1233593?lang=cat).
  También encontrará más información en los anexos del enunciado de esta práctica.

  Incluya, a continuación, una explicación de las técnicas incorporadas al detector. Se valorará la
  inclusión de gráficas, tablas, código o cualquier otra cosa que ayude a comprender el trabajo realizado.

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.
   

Evaluación *ciega* del detector
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
detector con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
