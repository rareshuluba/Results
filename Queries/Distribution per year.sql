SELECT 
	EXTRACT(year FROM dob) AS year,
	COUNT(*)*100./(SELECT COUNT(*) FROM public.patients) AS persons_per_year
FROM public.patients
GROUP BY EXTRACT(year FROM dob)
ORDER BY year 


