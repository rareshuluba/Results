SELECT CASE WHEN(
(SELECT 
	SUM(EXTRACT(year FROM dob))
FROM public.patients  
WHERE EXTRACT(year FROM dob)>1989 and EXTRACT(year FROM dob)<2000
)
>
(SELECT
	COUNT(*) 
	FROM public.patients
	WHERE name LIKE '%^FIG%'
)
)
THEN CAST(1 AS BIT)
ELSE CAST(0 AS BIT) 
END
