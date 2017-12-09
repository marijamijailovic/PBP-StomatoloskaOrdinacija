-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema StomatoloskaOrdinacija
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `StomatoloskaOrdinacija` ;

-- -----------------------------------------------------
-- Schema StomatoloskaOrdinacija
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `StomatoloskaOrdinacija` DEFAULT CHARACTER SET utf8 ;
USE `StomatoloskaOrdinacija` ;

-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Pacijent`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Pacijent` (
  `idPacijent` INT NOT NULL AUTO_INCREMENT,
  `Ime` VARCHAR(20) NOT NULL,
  `Prezime` VARCHAR(50) NOT NULL,
  `DatumRodjenja` DATE NOT NULL,
  `Adresa` VARCHAR(45) NOT NULL,
  `Telefon` VARCHAR(20) NOT NULL,
  `DatumOtvaranjaKartona` DATE NOT NULL,
  `UkupanDug` INT NOT NULL,
  `Placeno` TINYINT(1) NOT NULL,
  `Napomena` TEXT NOT NULL,
  PRIMARY KEY (`idPacijent`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Zaposleni`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Zaposleni` (
  `idZaposlenog` INT NOT NULL AUTO_INCREMENT,
  `Ime` VARCHAR(20) NOT NULL,
  `Prezime` VARCHAR(50) NOT NULL,
  PRIMARY KEY (`idZaposlenog`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Tehnicar`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Tehnicar` (
  `idTehnicara` INT NOT NULL,
  `RadnoIskustvo` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`idTehnicara`),
  INDEX `fk_Tehnicar_Zaposleni_idx` (`idTehnicara` ASC),
  CONSTRAINT `fk_Tehnicar_Zaposleni`
    FOREIGN KEY (`idTehnicara`)
    REFERENCES `StomatoloskaOrdinacija`.`Zaposleni` (`idZaposlenog`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Stomatolog`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Stomatolog` (
  `idStomatologa` INT NOT NULL,
  `Status` VARCHAR(45) NOT NULL,
  `RadnoIskustvo` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`idStomatologa`),
  INDEX `fk_Stomatolog_Zaposleni1_idx` (`idStomatologa` ASC),
  CONSTRAINT `fk_Stomatolog_Zaposleni1`
    FOREIGN KEY (`idStomatologa`)
    REFERENCES `StomatoloskaOrdinacija`.`Zaposleni` (`idZaposlenog`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Zub`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Zub` (
  `idZub` INT NOT NULL,
  PRIMARY KEY (`idZub`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`OblastIntervencije`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`OblastIntervencije` (
  `idOblastInt` INT NOT NULL AUTO_INCREMENT,
  `NazivOblasti` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idOblastInt`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`SpisakIntervencija`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`SpisakIntervencija` (
  `idSpisak` INT NOT NULL AUTO_INCREMENT,
  `NazivIntervencije` VARCHAR(45) NOT NULL,
  `Cena` DOUBLE NOT NULL,
  `idOblastInt` INT NOT NULL,
  PRIMARY KEY (`idSpisak`),
  INDEX `fk_Spisak_Intervencija_OblastIntervencije1_idx` (`idOblastInt` ASC),
  CONSTRAINT `fk_Spisak_Intervencija_OblastIntervencije1`
    FOREIGN KEY (`idOblastInt`)
    REFERENCES `StomatoloskaOrdinacija`.`OblastIntervencije` (`idOblastInt`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Zahvat`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Zahvat` (
  `sifra` INT NOT NULL AUTO_INCREMENT,
  `Datum` DATE NOT NULL,
  `idPacijent` INT NOT NULL,
  `idSpisak` INT NOT NULL,
  `idZub` INT NOT NULL,
  `idStomatologa` INT NOT NULL,
  `idTehnicara` INT NOT NULL,
  PRIMARY KEY (`sifra`),
  INDEX `fk_Intervencija_Pacijent1_idx` (`idPacijent` ASC),
  INDEX `fk_Intervencija_Intervencije1_idx` (`idSpisak` ASC),
  INDEX `fk_Intervencija_Zub1_idx` (`idZub` ASC),
  INDEX `fk_Intervencija_Stomatolog1_idx` (`idStomatologa` ASC),
  INDEX `fk_Intervencija_Tehnicar1_idx` (`idTehnicara` ASC),
  CONSTRAINT `fk_Intervencija_Pacijent1`
    FOREIGN KEY (`idPacijent`)
    REFERENCES `StomatoloskaOrdinacija`.`Pacijent` (`idPacijent`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Intervencija_Intervencije1`
    FOREIGN KEY (`idSpisak`)
    REFERENCES `StomatoloskaOrdinacija`.`SpisakIntervencija` (`idSpisak`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Intervencija_Zub1`
    FOREIGN KEY (`idZub`)
    REFERENCES `StomatoloskaOrdinacija`.`Zub` (`idZub`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Intervencija_Stomatolog1`
    FOREIGN KEY (`idStomatologa`)
    REFERENCES `StomatoloskaOrdinacija`.`Stomatolog` (`idStomatologa`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Intervencija_Tehnicar1`
    FOREIGN KEY (`idTehnicara`)
    REFERENCES `StomatoloskaOrdinacija`.`Tehnicar` (`idTehnicara`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Stolica`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Stolica` (
  `idOprema` INT NOT NULL AUTO_INCREMENT,
  `BrojStolice` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idOprema`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Obavlja`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Obavlja` (
  `Intervencija_idIntervencija` INT NOT NULL,
  `Stolica_idOprema` INT NOT NULL,
  PRIMARY KEY (`Intervencija_idIntervencija`),
  INDEX `fk_Stolica_has_Intervencija_Intervencija1_idx` (`Intervencija_idIntervencija` ASC),
  INDEX `fk_Stolica_has_Intervencija_Stolica1_idx` (`Stolica_idOprema` ASC),
  CONSTRAINT `fk_Stolica_has_Intervencija_Stolica1`
    FOREIGN KEY (`Stolica_idOprema`)
    REFERENCES `StomatoloskaOrdinacija`.`Stolica` (`idOprema`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Stolica_has_Intervencija_Intervencija1`
    FOREIGN KEY (`Intervencija_idIntervencija`)
    REFERENCES `StomatoloskaOrdinacija`.`Zahvat` (`sifra`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`ZatecenoStanje`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`ZatecenoStanje` (
  `idPacijent` INT NOT NULL,
  `Z0` VARCHAR(10) NOT NULL,
  `Z1` VARCHAR(10) NOT NULL,
  `Z2` VARCHAR(10) NOT NULL,
  `Z3` VARCHAR(10) NOT NULL,
  `Z4` VARCHAR(10) NOT NULL,
  `Z5` VARCHAR(10) NOT NULL,
  `Z6` VARCHAR(10) NOT NULL,
  `Z7` VARCHAR(10) NOT NULL,
  `Z8` VARCHAR(10) NOT NULL,
  `Z9` VARCHAR(10) NOT NULL,
  `Z10` VARCHAR(10) NOT NULL,
  `Z11` VARCHAR(10) NOT NULL,
  `Z12` VARCHAR(10) NOT NULL,
  `Z13` VARCHAR(10) NOT NULL,
  `Z14` VARCHAR(10) NOT NULL,
  `Z15` VARCHAR(10) NOT NULL,
  `Z16` VARCHAR(10) NOT NULL,
  `Z17` VARCHAR(10) NOT NULL,
  `Z18` VARCHAR(10) NOT NULL,
  `Z19` VARCHAR(10) NOT NULL,
  `Z20` VARCHAR(10) NOT NULL,
  `Z21` VARCHAR(10) NOT NULL,
  `Z22` VARCHAR(10) NOT NULL,
  `Z23` VARCHAR(10) NOT NULL,
  `Z24` VARCHAR(10) NOT NULL,
  `Z25` VARCHAR(10) NOT NULL,
  `Z26` VARCHAR(10) NOT NULL,
  `Z27` VARCHAR(10) NOT NULL,
  `Z28` VARCHAR(10) NOT NULL,
  `Z29` VARCHAR(10) NOT NULL,
  `Z30` VARCHAR(20) NOT NULL,
  `Z31` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`idPacijent`),
  INDEX `fk_PocetnoStanje_Pacijent1_idx` (`idPacijent` ASC),
  CONSTRAINT `fk_PocetnoStanje_Pacijent1`
    FOREIGN KEY (`idPacijent`)
    REFERENCES `StomatoloskaOrdinacija`.`Pacijent` (`idPacijent`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Materijal`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Materijal` (
  `idMaterijal` INT NOT NULL AUTO_INCREMENT,
  `naziv` VARCHAR(60) NOT NULL,
  PRIMARY KEY (`idMaterijal`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `StomatoloskaOrdinacija`.`Koristi`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `StomatoloskaOrdinacija`.`Koristi` (
  `SpisakIntervencija_idSpisak` INT NOT NULL,
  `Materijal_idMaterijal` INT NOT NULL,
  PRIMARY KEY (`SpisakIntervencija_idSpisak`, `Materijal_idMaterijal`),
  INDEX `fk_SpisakIntervencija_has_Materijal_Materijal1_idx` (`Materijal_idMaterijal` ASC),
  INDEX `fk_SpisakIntervencija_has_Materijal_SpisakIntervencija1_idx` (`SpisakIntervencija_idSpisak` ASC),
  CONSTRAINT `fk_SpisakIntervencija_has_Materijal_SpisakIntervencija1`
    FOREIGN KEY (`SpisakIntervencija_idSpisak`)
    REFERENCES `StomatoloskaOrdinacija`.`SpisakIntervencija` (`idSpisak`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_SpisakIntervencija_has_Materijal_Materijal1`
    FOREIGN KEY (`Materijal_idMaterijal`)
    REFERENCES `StomatoloskaOrdinacija`.`Materijal` (`idMaterijal`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
