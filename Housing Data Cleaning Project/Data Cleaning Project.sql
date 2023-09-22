SELECT *
FROM DataCleaning.dbo.Housing_Data

-- Date format
SELECT SaleDate, CONVERT(Date,SaleDate)
FROM DataCleaning.dbo.Housing_Data

Update Housing_Data
SET SaleDate = CONVERT(Date, SaleDate)
ALTER TABLE Housing_Data ALTER COLUMN SaleDate DATE

-- Populate property address
SELECT PropertyAddress
FROM DataCleaning.dbo.Housing_Data
--WHERE PropertyAddress is null
ORDER BY ParcelID


SELECT a.ParcelID, a.PropertyAddress, b.ParcelID, b.PropertyAddress, ISNULL(a.PropertyAddress,b.PropertyAddress)
FROM DataCleaning.dbo.Housing_Data a
JOIN DataCleaning.dbo.Housing_Data b
  on a.ParcelID = b.ParcelID
  AND a.[UniqueID ] <> b.[UniqueID ]
WHERE a.PropertyAddress is null

UPDATE a
SET PropertyAddress = ISNULL(a.PropertyAddress,b.PropertyAddress)
FROM DataCleaning.dbo.Housing_Data a
JOIN DataCleaning.dbo.Housing_Data b
  on a.ParcelID = b.ParcelID
  AND a.[UniqueID ] <> b.[UniqueID ]


-- Breaking out address into individual columns(Address, city, state)
SELECT PropertyAddress
FROM DataCleaning.dbo.Housing_Data

SELECT
SUBSTRING(PropertyAddress, 1, CHARINDEX(',', PropertyAddress)-1) as Address
, SUBSTRING(PropertyAddress, CHARINDEX(',', PropertyAddress)+1, LEN(PropertyAddress)) as Address
FROM DataCleaning.dbo.Housing_Data

ALTER TABLE Housing_data
Add PropertySplitAddress Nvarchar(300);

Update Housing_Data
SET PropertySplitAddress = SUBSTRING(PropertyAddress, 1, CHARINDEX(',', PropertyAddress)-1)

ALTER TABLE Housing_data
Add PropertySplitCity Nvarchar(300);

Update Housing_Data
SET PropertySplitCity = SUBSTRING(PropertyAddress, CHARINDEX(',', PropertyAddress)+1, LEN(PropertyAddress))

SELECT *
FROM DataCleaning.dbo.Housing_Data

SELECT OwnerAddress
FROM DataCleaning.dbo.Housing_Data

SELECT
PARSENAME(REPLACE(OwnerAddress, ',', '.'),3)
, PARSENAME(REPLACE(OwnerAddress, ',', '.'),2)
, PARSENAME(REPLACE(OwnerAddress, ',', '.'),1)
FROM DataCleaning.dbo.Housing_Data

ALTER TABLE Housing_data
Add OwnerSplitAddress Nvarchar(300);

Update Housing_Data
SET OwnerSplitAddress = PARSENAME(REPLACE(OwnerAddress, ',', '.'),3)

ALTER TABLE Housing_data
Add OwnerSplitCity Nvarchar(300);

Update Housing_Data
SET OwnerSplitCity = PARSENAME(REPLACE(OwnerAddress, ',', '.'),2)

ALTER TABLE Housing_data
Add OwnerSplitState Nvarchar(300);


SELECT *
FROM DataCleaning.dbo.Housing_Data

-- changing Y and N to Yes and No in 'Sold as Vacant' field

Select Distinct(SoldAsVacant), COUNT(SoldAsVacant)
FROM DataCleaning.dbo.Housing_Data
GROUP BY SoldAsVacant
Order by 2

SELECT SoldAsVacant
, CASE WHEN SoldAsVacant = 'Y' THEN 'Yes'
       WHEN SoldAsVacant = 'N' THEN 'No'
	   ELSE SoldAsVacant
	   END
FROM DataCleaning.dbo.Housing_Data

UPDATE Housing_Data
SET SoldAsVacant = CASE WHEN SoldAsVacant = 'Y' THEN 'Yes'
       WHEN SoldAsVacant = 'N' THEN 'No'
	   ELSE SoldAsVacant
	   END


-- Removing Duplicates
WITH RowNumCTE AS(
SELECT *,
  ROW_NUMBER() OVER (
  PARTITION BY ParcelID,
               PropertyAddress,
			   SalePrice,
			   SaleDate,
			   LegalReference
			   ORDER BY
			     UniqueID
				 ) row_num

FROM DataCleaning.dbo.Housing_Data
)

SELECT *
FROM RowNumCTE
WHERE row_num>1


-- Delete unused columns
SELECT *
FROM DataCleaning.dbo.Housing_Data

ALTER TABLE DataCleaning.dbo.Housing_Data
DROP COLUMN OwnerAddress, TaxDistrict, PropertyAddress