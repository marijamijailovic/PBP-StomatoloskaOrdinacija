use StomatoloskaOrdinacija;

drop trigger if exists dug_iskustvo;

delimiter $

create trigger dug_iskustvo after insert on Zahvat
for each row
begin
	set @stomatologBrIntervencija = (select count(idStomatologa) from Zahvat where idStomatologa = new.idStomatologa);
	set @tehnicarBrIntervencija = (select count(idTehnicara) from Zahvat where idTehnicara = new.idTehnicara);

	if (@stomatologBrIntervencija > @countS) then
	begin
		set @countS = @countS + 10;
		Update Stomatolog set RadnoIskustvo = (RadnoIskustvo+3) where idStomatologa = new.idStomatologa;
	end;
	end if;

	if (@tehnicarBrIntervencija > @countT) then
	begin
		set @countT = @countT + 10;
		Update Tehnicar set RadnoIskustvo = (RadnoIskustvo+3) where idTehnicara = new.idTehnicara;
	end;
	end if;

	set @cena = (select Cena from SpisakIntervencija where idSpisak = new.idSpisak);
	update Pacijent set UkupanDug = UkupanDug+@cena where idPacijent = new.idPacijent;
end$

delimiter ;

set @cena = 0;
set @stomatologBrIntervencija = 0;
set @tehnicarBrIntervencija = 0;
set @countS = 10;
set @countT = 10;
