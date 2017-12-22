use StomatoloskaOrdinacija;

drop trigger if exists zub;
drop trigger if exists dug_iskustvo;

delimiter $

create trigger zub before insert on Zahvat
for each row
begin
	if(new.Zub not between 1 and 32) then
			signal sqlstate '45000' set message_text = "Zub mora biti broj izmedju 1 i 32";
	end if;
end$

create trigger dug_iskustvo after insert on Zahvat
for each row
begin
	set @stomatologBrIntervencija = (select count(idStomatologa) from Zahvat where idStomatologa = new.idStomatologa);
	set @tehnicarBrIntervencija = (select count(idTehnicara) from Zahvat where idTehnicara = new.idTehnicara);

  if (@stomatologBrIntervencija mod 10)=0 then
          update Stomatolog set RadnoIskustvo =
							case
									when RadnoIskustvo<98 then RadnoIskustvo+3
									when RadnoIskustvo>=98 then 100
							end
					where idStomatologa = new.idStomatologa;
	end if;

  if (@tehnicarBrIntervencija mod 10)=0 then
      update Tehnicar set RadnoIskustvo =
				case
						when RadnoIskustvo<98 then RadnoIskustvo+3
						when RadnoIskustvo>=98 then 100
				end
		 	where idTehnicara = new.idTehnicara;
	end if;

	set @cena = (select Cena from SpisakIntervencija where idSpisak = new.idSpisak);
	update Pacijent set UkupanDug = UkupanDug+@cena where idPacijent = new.idPacijent;
end$

delimiter ;

set @cena = 0;
set @stomatologBrIntervencija = 0;
set @tehnicarBrIntervencija = 0;
