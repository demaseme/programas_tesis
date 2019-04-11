#include "geom.h"

int n10(Segmento *segmentos, int nsegmentos, FILE *log){
	int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, intersectan, cont;
	// A partir de n = 10 buscar CF de tamaño 10
	cont = 0;
	
	for(i1 = 0; i1 < nsegmentos; i1++){
		for(i2 = i1+1; i2 < nsegmentos; i2++){
			intersectan = 1;
			intersectan &= interseccion(segmentos[i1], segmentos[i2]) || comparten_punto(segmentos[i1], segmentos[i2]);
			if(!intersectan) continue;
			for(i3 = i2+1; i3 < nsegmentos; i3++){
				intersectan = 1;
				intersectan &= interseccion(segmentos[i1], segmentos[i3]) || comparten_punto(segmentos[i1], segmentos[i3]);
				intersectan &= interseccion(segmentos[i2], segmentos[i3]) || comparten_punto(segmentos[i2], segmentos[i3]);
				if(!intersectan) continue;
				for(i4 = i3+1; i4 < nsegmentos; i4++){
					intersectan = 1;
					intersectan &= interseccion(segmentos[i1], segmentos[i4]) || comparten_punto(segmentos[i1], segmentos[i4]);
					intersectan &= interseccion(segmentos[i2], segmentos[i4]) || comparten_punto(segmentos[i2], segmentos[i4]);
					intersectan &= interseccion(segmentos[i3], segmentos[i4]) || comparten_punto(segmentos[i3], segmentos[i4]);
					if(!intersectan) continue;
					for(i5 = i4+1; i5 < nsegmentos; i5++){
						intersectan = 1;
						intersectan &= interseccion(segmentos[i1], segmentos[i5]) || comparten_punto(segmentos[i1], segmentos[i5]);
						intersectan &= interseccion(segmentos[i2], segmentos[i5]) || comparten_punto(segmentos[i2], segmentos[i5]);
						intersectan &= interseccion(segmentos[i3], segmentos[i5]) || comparten_punto(segmentos[i3], segmentos[i5]);
						intersectan &= interseccion(segmentos[i4], segmentos[i5]) || comparten_punto(segmentos[i4], segmentos[i5]);
						if(!intersectan) continue;
						for(i6 = i5+1; i6 < nsegmentos; i6++){
							intersectan = 1;
							intersectan &= interseccion(segmentos[i1], segmentos[i6]) || comparten_punto(segmentos[i1], segmentos[i6]);
							intersectan &= interseccion(segmentos[i2], segmentos[i6]) || comparten_punto(segmentos[i2], segmentos[i6]);
							intersectan &= interseccion(segmentos[i3], segmentos[i6]) || comparten_punto(segmentos[i3], segmentos[i6]);
							intersectan &= interseccion(segmentos[i4], segmentos[i6]) || comparten_punto(segmentos[i4], segmentos[i6]);
							intersectan &= interseccion(segmentos[i5], segmentos[i6]) || comparten_punto(segmentos[i5], segmentos[i6]);
							if(!intersectan) continue;
							for(i7 = i6+1; i7 < nsegmentos; i7++){
								intersectan = 1;
								intersectan &= interseccion(segmentos[i1], segmentos[i7]) || comparten_punto(segmentos[i1], segmentos[i7]);
								intersectan &= interseccion(segmentos[i2], segmentos[i7]) || comparten_punto(segmentos[i2], segmentos[i7]);
								intersectan &= interseccion(segmentos[i3], segmentos[i7]) || comparten_punto(segmentos[i3], segmentos[i7]);
								intersectan &= interseccion(segmentos[i4], segmentos[i7]) || comparten_punto(segmentos[i4], segmentos[i7]);
								intersectan &= interseccion(segmentos[i5], segmentos[i7]) || comparten_punto(segmentos[i5], segmentos[i7]);
								intersectan &= interseccion(segmentos[i6], segmentos[i7]) || comparten_punto(segmentos[i6], segmentos[i7]);
								if(!intersectan) continue;
								for(i8 = i7+1; i8 < nsegmentos; i8++){
									intersectan = 1;
									intersectan &= interseccion(segmentos[i1], segmentos[i8]) || comparten_punto(segmentos[i1], segmentos[i8]);
									intersectan &= interseccion(segmentos[i2], segmentos[i8]) || comparten_punto(segmentos[i2], segmentos[i8]);
									intersectan &= interseccion(segmentos[i3], segmentos[i8]) || comparten_punto(segmentos[i3], segmentos[i8]);
									intersectan &= interseccion(segmentos[i4], segmentos[i8]) || comparten_punto(segmentos[i4], segmentos[i8]);
									intersectan &= interseccion(segmentos[i5], segmentos[i8]) || comparten_punto(segmentos[i5], segmentos[i8]);
									intersectan &= interseccion(segmentos[i6], segmentos[i8]) || comparten_punto(segmentos[i6], segmentos[i8]);
									intersectan &= interseccion(segmentos[i7], segmentos[i8]) || comparten_punto(segmentos[i7], segmentos[i8]);
									if(!intersectan) continue;
									for(i9 = i8+1; i9 < nsegmentos; i9++){
										intersectan = 1;
										intersectan &= interseccion(segmentos[i1], segmentos[i9]) || comparten_punto(segmentos[i1], segmentos[i9]);
										intersectan &= interseccion(segmentos[i2], segmentos[i9]) || comparten_punto(segmentos[i2], segmentos[i9]);
										intersectan &= interseccion(segmentos[i3], segmentos[i9]) || comparten_punto(segmentos[i3], segmentos[i9]);
										intersectan &= interseccion(segmentos[i4], segmentos[i9]) || comparten_punto(segmentos[i4], segmentos[i9]);
										intersectan &= interseccion(segmentos[i5], segmentos[i9]) || comparten_punto(segmentos[i5], segmentos[i9]);
										intersectan &= interseccion(segmentos[i6], segmentos[i9]) || comparten_punto(segmentos[i6], segmentos[i9]);
										intersectan &= interseccion(segmentos[i7], segmentos[i9]) || comparten_punto(segmentos[i7], segmentos[i9]);
										intersectan &= interseccion(segmentos[i8], segmentos[i9]) || comparten_punto(segmentos[i8], segmentos[i9]);
										if(!intersectan) continue;
										for(i10 = i9+1; i10 < nsegmentos; i10++){
											intersectan = 1;
											intersectan &= interseccion(segmentos[i1], segmentos[i10]) || comparten_punto(segmentos[i1], segmentos[i10]);
											intersectan &= interseccion(segmentos[i2], segmentos[i10]) || comparten_punto(segmentos[i2], segmentos[i10]);
											intersectan &= interseccion(segmentos[i3], segmentos[i10]) || comparten_punto(segmentos[i3], segmentos[i10]);
											intersectan &= interseccion(segmentos[i4], segmentos[i10]) || comparten_punto(segmentos[i4], segmentos[i10]);
											intersectan &= interseccion(segmentos[i5], segmentos[i10]) || comparten_punto(segmentos[i5], segmentos[i10]);
											intersectan &= interseccion(segmentos[i6], segmentos[i10]) || comparten_punto(segmentos[i6], segmentos[i10]);
											intersectan &= interseccion(segmentos[i7], segmentos[i10]) || comparten_punto(segmentos[i7], segmentos[i10]);
											intersectan &= interseccion(segmentos[i8], segmentos[i10]) || comparten_punto(segmentos[i8], segmentos[i10]);
											intersectan &= interseccion(segmentos[i9], segmentos[i10]) || comparten_punto(segmentos[i9], segmentos[i10]);
											if(!intersectan) continue;
											fprintf(log, "%s%s%s%s%s%s%s%s%s%s\n", 
												segmentos[i1].etiqueta, segmentos[i2].etiqueta, segmentos[i3].etiqueta, segmentos[i4].etiqueta, segmentos[i5].etiqueta, 
												segmentos[i6].etiqueta, segmentos[i7].etiqueta, segmentos[i8].etiqueta, segmentos[i9].etiqueta, segmentos[i10].etiqueta);
											cont++;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return cont;
}

int n9(Segmento *segmentos, int nsegmentos, FILE *log){
	int i1, i2, i3, i4, i5, i6, i7, i8, i9, intersectan, cont;
	// A partir de n = 9 buscar CF de tamaño 9
	cont = 0;
	
	for(i1 = 0; i1 < nsegmentos; i1++){
		for(i2 = i1+1; i2 < nsegmentos; i2++){
			intersectan = 1;
			intersectan &= interseccion(segmentos[i1], segmentos[i2]) || comparten_punto(segmentos[i1], segmentos[i2]);
			if(!intersectan) continue;
			for(i3 = i2+1; i3 < nsegmentos; i3++){
				intersectan = 1;
				intersectan &= interseccion(segmentos[i1], segmentos[i3]) || comparten_punto(segmentos[i1], segmentos[i3]);
				intersectan &= interseccion(segmentos[i2], segmentos[i3]) || comparten_punto(segmentos[i2], segmentos[i3]);
				if(!intersectan) continue;
				for(i4 = i3+1; i4 < nsegmentos; i4++){
					intersectan = 1;
					intersectan &= interseccion(segmentos[i1], segmentos[i4]) || comparten_punto(segmentos[i1], segmentos[i4]);
					intersectan &= interseccion(segmentos[i2], segmentos[i4]) || comparten_punto(segmentos[i2], segmentos[i4]);
					intersectan &= interseccion(segmentos[i3], segmentos[i4]) || comparten_punto(segmentos[i3], segmentos[i4]);
					if(!intersectan) continue;
					for(i5 = i4+1; i5 < nsegmentos; i5++){
						intersectan = 1;
						intersectan &= interseccion(segmentos[i1], segmentos[i5]) || comparten_punto(segmentos[i1], segmentos[i5]);
						intersectan &= interseccion(segmentos[i2], segmentos[i5]) || comparten_punto(segmentos[i2], segmentos[i5]);
						intersectan &= interseccion(segmentos[i3], segmentos[i5]) || comparten_punto(segmentos[i3], segmentos[i5]);
						intersectan &= interseccion(segmentos[i4], segmentos[i5]) || comparten_punto(segmentos[i4], segmentos[i5]);
						if(!intersectan) continue;
						for(i6 = i5+1; i6 < nsegmentos; i6++){
							intersectan = 1;
							intersectan &= interseccion(segmentos[i1], segmentos[i6]) || comparten_punto(segmentos[i1], segmentos[i6]);
							intersectan &= interseccion(segmentos[i2], segmentos[i6]) || comparten_punto(segmentos[i2], segmentos[i6]);
							intersectan &= interseccion(segmentos[i3], segmentos[i6]) || comparten_punto(segmentos[i3], segmentos[i6]);
							intersectan &= interseccion(segmentos[i4], segmentos[i6]) || comparten_punto(segmentos[i4], segmentos[i6]);
							intersectan &= interseccion(segmentos[i5], segmentos[i6]) || comparten_punto(segmentos[i5], segmentos[i6]);
							if(!intersectan) continue;
							for(i7 = i6+1; i7 < nsegmentos; i7++){
								intersectan = 1;
								intersectan &= interseccion(segmentos[i1], segmentos[i7]) || comparten_punto(segmentos[i1], segmentos[i7]);
								intersectan &= interseccion(segmentos[i2], segmentos[i7]) || comparten_punto(segmentos[i2], segmentos[i7]);
								intersectan &= interseccion(segmentos[i3], segmentos[i7]) || comparten_punto(segmentos[i3], segmentos[i7]);
								intersectan &= interseccion(segmentos[i4], segmentos[i7]) || comparten_punto(segmentos[i4], segmentos[i7]);
								intersectan &= interseccion(segmentos[i5], segmentos[i7]) || comparten_punto(segmentos[i5], segmentos[i7]);
								intersectan &= interseccion(segmentos[i6], segmentos[i7]) || comparten_punto(segmentos[i6], segmentos[i7]);
								if(!intersectan) continue;
								for(i8 = i7+1; i8 < nsegmentos; i8++){
									intersectan = 1;
									intersectan &= interseccion(segmentos[i1], segmentos[i8]) || comparten_punto(segmentos[i1], segmentos[i8]);
									intersectan &= interseccion(segmentos[i2], segmentos[i8]) || comparten_punto(segmentos[i2], segmentos[i8]);
									intersectan &= interseccion(segmentos[i3], segmentos[i8]) || comparten_punto(segmentos[i3], segmentos[i8]);
									intersectan &= interseccion(segmentos[i4], segmentos[i8]) || comparten_punto(segmentos[i4], segmentos[i8]);
									intersectan &= interseccion(segmentos[i5], segmentos[i8]) || comparten_punto(segmentos[i5], segmentos[i8]);
									intersectan &= interseccion(segmentos[i6], segmentos[i8]) || comparten_punto(segmentos[i6], segmentos[i8]);
									intersectan &= interseccion(segmentos[i7], segmentos[i8]) || comparten_punto(segmentos[i7], segmentos[i8]);
									if(!intersectan) continue;
									for(i9 = i8+1; i9 < nsegmentos; i9++){
										intersectan = 1;
										intersectan &= interseccion(segmentos[i1], segmentos[i9]) || comparten_punto(segmentos[i1], segmentos[i9]);
										intersectan &= interseccion(segmentos[i2], segmentos[i9]) || comparten_punto(segmentos[i2], segmentos[i9]);
										intersectan &= interseccion(segmentos[i3], segmentos[i9]) || comparten_punto(segmentos[i3], segmentos[i9]);
										intersectan &= interseccion(segmentos[i4], segmentos[i9]) || comparten_punto(segmentos[i4], segmentos[i9]);
										intersectan &= interseccion(segmentos[i5], segmentos[i9]) || comparten_punto(segmentos[i5], segmentos[i9]);
										intersectan &= interseccion(segmentos[i6], segmentos[i9]) || comparten_punto(segmentos[i6], segmentos[i9]);
										intersectan &= interseccion(segmentos[i7], segmentos[i9]) || comparten_punto(segmentos[i7], segmentos[i9]);
										intersectan &= interseccion(segmentos[i8], segmentos[i9]) || comparten_punto(segmentos[i8], segmentos[i9]);
										if(!intersectan) continue;

											fprintf(log, "%s%s%s%s%s%s%s%s%s\n", 
												segmentos[i1].etiqueta, segmentos[i2].etiqueta, segmentos[i3].etiqueta, segmentos[i4].etiqueta, segmentos[i5].etiqueta, 
												segmentos[i6].etiqueta, segmentos[i7].etiqueta, segmentos[i8].etiqueta, segmentos[i9].etiqueta);
											cont++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return cont;
}

int n8(Segmento *segmentos, int nsegmentos, FILE *log){
	int i1, i2, i3, i4, i5, i6, i7, i8, intersectan, cont;
	// A partir de n = 8 buscar CF de tamaño 8
	cont = 0;

	for(i1 = 0; i1 < nsegmentos; i1++){
		for(i2 = i1+1; i2 < nsegmentos; i2++){
			intersectan = 1;
			intersectan &= interseccion(segmentos[i1], segmentos[i2]) || comparten_punto(segmentos[i1], segmentos[i2]);
			if(!intersectan) continue;
			for(i3 = i2+1; i3 < nsegmentos; i3++){
				intersectan = 1;
				intersectan &= interseccion(segmentos[i1], segmentos[i3]) || comparten_punto(segmentos[i1], segmentos[i3]);
				intersectan &= interseccion(segmentos[i2], segmentos[i3]) || comparten_punto(segmentos[i2], segmentos[i3]);
				if(!intersectan) continue;
				for(i4 = i3+1; i4 < nsegmentos; i4++){
					intersectan = 1;
					intersectan &= interseccion(segmentos[i1], segmentos[i4]) || comparten_punto(segmentos[i1], segmentos[i4]);
					intersectan &= interseccion(segmentos[i2], segmentos[i4]) || comparten_punto(segmentos[i2], segmentos[i4]);
					intersectan &= interseccion(segmentos[i3], segmentos[i4]) || comparten_punto(segmentos[i3], segmentos[i4]);
					if(!intersectan) continue;
					for(i5 = i4+1; i5 < nsegmentos; i5++){
						intersectan = 1;
						intersectan &= interseccion(segmentos[i1], segmentos[i5]) || comparten_punto(segmentos[i1], segmentos[i5]);
						intersectan &= interseccion(segmentos[i2], segmentos[i5]) || comparten_punto(segmentos[i2], segmentos[i5]);
						intersectan &= interseccion(segmentos[i3], segmentos[i5]) || comparten_punto(segmentos[i3], segmentos[i5]);
						intersectan &= interseccion(segmentos[i4], segmentos[i5]) || comparten_punto(segmentos[i4], segmentos[i5]);
						if(!intersectan) continue;
						for(i6 = i5+1; i6 < nsegmentos; i6++){
							intersectan = 1;
							intersectan &= interseccion(segmentos[i1], segmentos[i6]) || comparten_punto(segmentos[i1], segmentos[i6]);
							intersectan &= interseccion(segmentos[i2], segmentos[i6]) || comparten_punto(segmentos[i2], segmentos[i6]);
							intersectan &= interseccion(segmentos[i3], segmentos[i6]) || comparten_punto(segmentos[i3], segmentos[i6]);
							intersectan &= interseccion(segmentos[i4], segmentos[i6]) || comparten_punto(segmentos[i4], segmentos[i6]);
							intersectan &= interseccion(segmentos[i5], segmentos[i6]) || comparten_punto(segmentos[i5], segmentos[i6]);
							if(!intersectan) continue;
							for(i7 = i6+1; i7 < nsegmentos; i7++){
								intersectan = 1;
								intersectan &= interseccion(segmentos[i1], segmentos[i7]) || comparten_punto(segmentos[i1], segmentos[i7]);
								intersectan &= interseccion(segmentos[i2], segmentos[i7]) || comparten_punto(segmentos[i2], segmentos[i7]);
								intersectan &= interseccion(segmentos[i3], segmentos[i7]) || comparten_punto(segmentos[i3], segmentos[i7]);
								intersectan &= interseccion(segmentos[i4], segmentos[i7]) || comparten_punto(segmentos[i4], segmentos[i7]);
								intersectan &= interseccion(segmentos[i5], segmentos[i7]) || comparten_punto(segmentos[i5], segmentos[i7]);
								intersectan &= interseccion(segmentos[i6], segmentos[i7]) || comparten_punto(segmentos[i6], segmentos[i7]);
								if(!intersectan) continue;
								for(i8 = i7+1; i8 < nsegmentos; i8++){
									intersectan = 1;
									intersectan &= interseccion(segmentos[i1], segmentos[i8]) || comparten_punto(segmentos[i1], segmentos[i8]);
									intersectan &= interseccion(segmentos[i2], segmentos[i8]) || comparten_punto(segmentos[i2], segmentos[i8]);
									intersectan &= interseccion(segmentos[i3], segmentos[i8]) || comparten_punto(segmentos[i3], segmentos[i8]);
									intersectan &= interseccion(segmentos[i4], segmentos[i8]) || comparten_punto(segmentos[i4], segmentos[i8]);
									intersectan &= interseccion(segmentos[i5], segmentos[i8]) || comparten_punto(segmentos[i5], segmentos[i8]);
									intersectan &= interseccion(segmentos[i6], segmentos[i8]) || comparten_punto(segmentos[i6], segmentos[i8]);
									intersectan &= interseccion(segmentos[i7], segmentos[i8]) || comparten_punto(segmentos[i7], segmentos[i8]);
									if(!intersectan) continue;
										fprintf(log, "%s%s%s%s%s%s%s%s\n", 
											segmentos[i1].etiqueta, segmentos[i2].etiqueta, segmentos[i3].etiqueta, segmentos[i4].etiqueta, segmentos[i5].etiqueta, 
											segmentos[i6].etiqueta, segmentos[i7].etiqueta, segmentos[i8].etiqueta);
										cont++;
								}
							}
						}
					}
				}
			}
		}
	}
	return cont;
}

int n6(Segmento *segmentos, int nsegmentos, FILE *log){
	int i1, i2, i3, i4, i5, i6, intersectan, cont;
	// A partir de n = 8 buscar CF de tamaño 8
	cont = 0;

	for(i1 = 0; i1 < nsegmentos; i1++){
		for(i2 = i1+1; i2 < nsegmentos; i2++){
			intersectan = 1;
			intersectan &= interseccion(segmentos[i1], segmentos[i2]) || comparten_punto(segmentos[i1], segmentos[i2]);
			if(!intersectan) continue;
			for(i3 = i2+1; i3 < nsegmentos; i3++){
				intersectan = 1;
				intersectan &= interseccion(segmentos[i1], segmentos[i3]) || comparten_punto(segmentos[i1], segmentos[i3]);
				intersectan &= interseccion(segmentos[i2], segmentos[i3]) || comparten_punto(segmentos[i2], segmentos[i3]);
				if(!intersectan) continue;
				for(i4 = i3+1; i4 < nsegmentos; i4++){
					intersectan = 1;
					intersectan &= interseccion(segmentos[i1], segmentos[i4]) || comparten_punto(segmentos[i1], segmentos[i4]);
					intersectan &= interseccion(segmentos[i2], segmentos[i4]) || comparten_punto(segmentos[i2], segmentos[i4]);
					intersectan &= interseccion(segmentos[i3], segmentos[i4]) || comparten_punto(segmentos[i3], segmentos[i4]);
					if(!intersectan) continue;
					for(i5 = i4+1; i5 < nsegmentos; i5++){
						intersectan = 1;
						intersectan &= interseccion(segmentos[i1], segmentos[i5]) || comparten_punto(segmentos[i1], segmentos[i5]);
						intersectan &= interseccion(segmentos[i2], segmentos[i5]) || comparten_punto(segmentos[i2], segmentos[i5]);
						intersectan &= interseccion(segmentos[i3], segmentos[i5]) || comparten_punto(segmentos[i3], segmentos[i5]);
						intersectan &= interseccion(segmentos[i4], segmentos[i5]) || comparten_punto(segmentos[i4], segmentos[i5]);
						if(!intersectan) continue;
						for(i6 = i5+1; i6 < nsegmentos; i6++){
							intersectan = 1;
							intersectan &= interseccion(segmentos[i1], segmentos[i6]) || comparten_punto(segmentos[i1], segmentos[i6]);
							intersectan &= interseccion(segmentos[i2], segmentos[i6]) || comparten_punto(segmentos[i2], segmentos[i6]);
							intersectan &= interseccion(segmentos[i3], segmentos[i6]) || comparten_punto(segmentos[i3], segmentos[i6]);
							intersectan &= interseccion(segmentos[i4], segmentos[i6]) || comparten_punto(segmentos[i4], segmentos[i6]);
							intersectan &= interseccion(segmentos[i5], segmentos[i6]) || comparten_punto(segmentos[i5], segmentos[i6]);
							if(!intersectan) continue;
							fprintf(log, "%s%s%s%s%s%s\n", 
								segmentos[i1].etiqueta, segmentos[i2].etiqueta, segmentos[i3].etiqueta, segmentos[i4].etiqueta, segmentos[i5].etiqueta, 
								segmentos[i6].etiqueta);							
							cont++;
						}
					}
				}
			}
		}
	}
	return cont;
}