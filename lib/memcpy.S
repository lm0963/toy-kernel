global memcpy
memcpy:
	mov	esi,[esp+4]
	mov	edi,[esp+8]
	mov	ecx,[esp+12]
	rep	movsb
	ret
